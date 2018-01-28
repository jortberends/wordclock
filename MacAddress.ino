extern "C" {
  #include <user_interface.h>
}

void setupMacAddress() {
  uint8_t mac[6] {0xA8, 0xD9, 0xB3, 0x0D, 0xAA, 0xCE};
  wifi_set_macaddr(0, const_cast<uint8*>(mac));
}

