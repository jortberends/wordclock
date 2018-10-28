#include <WiFiUdp.h>
#include <Time.h>
#include <TimeLib.h>
#include <DS1302.h>

// RTC: CE, IO, CLK 
DS1302 rtc(16, 5, 4);

// Local port to listen for UDP packets
unsigned int NTP_LOCAL_PORT = 2390;
IPAddress NTP_SERVER_IP;
const char* NTP_SERVER_NAME = "pool.ntp.org";
const int NTP_PACKET_SIZE = 48; // NTP time stamp is in the first 48 bytes of message
byte NTP_PACKET_BUFFER[NTP_PACKET_SIZE]; // Buffer to hold in/out-coming packets
WiFiUDP udp;

void setupTime() {
  setupNTPServer();
  setupRTC();
  readTimeAndSetRTC();
  stopNTPServer();
}

void setupNTPServer() {
  Serial.println("Starting UDP");
  udp.begin(NTP_LOCAL_PORT);
  Serial.print("Local port: ");
  Serial.println(udp.localPort());
}

void stopNTPServer() {
  udp.stop();
}

void setupRTC() {
  rtc.writeProtect(false);
  rtc.halt(false);
}

void readTimeAndSetRTC() {
  time_t t = retrieveTime();
  
  Serial.print("Time: ");
  Serial.println(t);

  Time rtcTime = Time(year(t), month(t), day(t), hour(t), minute(t), second(t), Time::kSunday);

  rtc.time(rtcTime);

  Serial.println("RTC is set");
}

unsigned long retrieveTime()
{ 
  printStatusPixel();
  
  unsigned long result;
  
  //get a random server from the pool
  WiFi.hostByName(NTP_SERVER_NAME, NTP_SERVER_IP); 

  sendNTPpacket(NTP_SERVER_IP); // send an NTP packet to a time server
  // wait to see if a reply is available
  delay(1000);

  int cb = udp.parsePacket();

  if (cb) {
    
    Serial.print("packet received, length=");
    Serial.println(cb);
    // We've received a packet, read the data from it
    udp.read(NTP_PACKET_BUFFER, NTP_PACKET_SIZE); // read the packet into the buffer
  
    //the timestamp starts at byte 40 of the received packet and is four bytes,
    // or two words, long. First, esxtract the two words:
  
    unsigned long highWord = word(NTP_PACKET_BUFFER[40], NTP_PACKET_BUFFER[41]);
    unsigned long lowWord = word(NTP_PACKET_BUFFER[42], NTP_PACKET_BUFFER[43]);
    // combine the four bytes (two words) into a long integer
    // this is NTP time (seconds since Jan 1 1900):
    unsigned long secsSince1900 = highWord << 16 | lowWord;
    Serial.print("Seconds since Jan 1 1900 = " );
    Serial.println(secsSince1900);
  
    // now convert NTP time into everyday time:
    Serial.print("Unix time = ");
    // Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
    const unsigned long seventyYears = 2208988800UL;
    // subtract seventy years:
    unsigned long epoch = secsSince1900 - seventyYears;
    // print Unix time:
    Serial.println(epoch);
  
    // print the hour, minute and second:
    Serial.print("The UTC time is ");       // UTC is the time at Greenwich Meridian (GMT)
    Serial.print((epoch  % 86400L) / 3600); // print the hour (86400 equals secs per day)
    Serial.print(':');
    if ( ((epoch % 3600) / 60) < 10 ) {
      // In the first 10 minutes of each hour, we'll want a leading '0'
      Serial.print('0');
    }
    Serial.print((epoch  % 3600) / 60); // print the minute (3600 equals secs per minute)
    Serial.print(':');
    if ( (epoch % 60) < 10 ) {
      // In the first 10 seconds of each minute, we'll want a leading '0'
      Serial.print('0');
    }
    Serial.println(epoch % 60); // print the second
  
    epoch = epoch + 60*60*TIMEZONE;
    // print the hour, minute and second:
    Serial.print("The UTC time is ");       // UTC is the time at Greenwich Meridian (GMT)
    Serial.print((epoch  % 86400L) / 3600); // print the hour (86400 equals secs per day)
    Serial.print(':');
    if ( ((epoch % 3600) / 60) < 10 ) {
      // In the first 10 minutes of each hour, we'll want a leading '0'
      Serial.print('0');
    }
    Serial.print((epoch  % 3600) / 60); // print the minute (3600 equals secs per minute)
    Serial.print(':');
    if ( (epoch % 60) < 10 ) {
      // In the first 10 seconds of each minute, we'll want a leading '0'
      Serial.print('0');
    }
    Serial.println(epoch % 60); // print the second
  
    result = epoch;
  } else {
    printStatusPixel();
    delay(10000);
    return retrieveTime();
  }
 
  return result;
}

// send an NTP request to the time server at the given address
unsigned long sendNTPpacket(IPAddress& address)
{
  Serial.println("sending NTP packet...");
  // set all bytes in the buffer to 0
  memset(NTP_PACKET_BUFFER, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  NTP_PACKET_BUFFER[0] = 0b11100011;   // LI, Version, Mode
  NTP_PACKET_BUFFER[1] = 0;     // Stratum, or type of clock
  NTP_PACKET_BUFFER[2] = 6;     // Polling Interval
  NTP_PACKET_BUFFER[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  NTP_PACKET_BUFFER[12]  = 49;
  NTP_PACKET_BUFFER[13]  = 0x4E;
  NTP_PACKET_BUFFER[14]  = 49;
  NTP_PACKET_BUFFER[15]  = 52;

  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  udp.beginPacket(address, 123); //NTP requests are to port 123
  udp.write(NTP_PACKET_BUFFER, NTP_PACKET_SIZE);
  udp.endPacket();
}

