#define MATRIX_HEIGHT 10
#define MATRIX_WIDTH 11

typedef struct
{
  unsigned char r;
  unsigned char g;
  unsigned char b;
} ColorRGB;

//a color with 3 components: h, s and v
typedef struct 
{
  unsigned char h;
  unsigned char s;
  unsigned char v;
} ColorHSV;

//these values are substracetd from the generated values to give a shape to the animation
const unsigned char valueMask[MATRIX_HEIGHT][MATRIX_WIDTH]={
    {25 , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 25 },
    {50 , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 50 },
    {75 , 25 , 0  , 0  , 0  , 0  , 0  , 0  , 0  , 25 , 75 },
    {100, 50 , 25 , 0  , 0  , 0  , 0  , 0  , 25 , 50 , 100},
    {125, 75 , 50 , 25 , 0  , 0  , 0  , 25 , 50 , 75 , 125},
    {150, 100, 75 , 50 , 25 , 0  , 25 , 50 , 75 , 100, 150},
    {175, 125, 100, 75 , 50 , 25 , 50 , 75 , 100, 125, 175},
    {200, 150, 125, 100, 75 , 50 , 75 , 100, 125, 150, 200},
    {225, 175, 150, 125, 100, 75 , 100, 125, 150, 175, 125},
    {255, 200, 175, 150, 125, 100, 125, 150, 175, 200, 255}
};

//these are the hues for the fire, 
//should be between 0 (red) to about 13 (yellow)
const unsigned char hueMask[MATRIX_HEIGHT][MATRIX_WIDTH]={
    {1 , 4 , 5 , 7 , 8 , 9 , 8 , 7 , 5 , 4 , 1},
    {1 , 4 , 4 , 5 , 6 , 7 , 6 , 5 , 4 , 4 , 1},
    {1 , 3 , 4 , 5 , 5 , 6 , 5 , 5 , 4 , 3 , 1},
    {1 , 3 , 3 , 4 , 4 , 5 , 4 , 4 , 3 , 3 , 1},
    {1 , 2 , 3 , 3 , 4 , 4 , 4 , 3 , 3 , 2 , 1},
    {0 , 1 , 2 , 2 , 3 , 3 , 3 , 2 , 2 , 1 , 0},
    {0 , 1 , 1 , 1 , 2 , 2 , 2 , 1 , 1 , 0 , 0},
    {0 , 0 , 0 , 1 , 1 , 2 , 2 , 1 , 0 , 0 , 0},
    {0 , 0 , 0 , 0 , 1 , 1 , 1 , 0 , 0 , 0 , 0},
    {0 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0}
};

const unsigned char mapMatrix[MATRIX_HEIGHT][MATRIX_WIDTH] = {
  {109, 108, 107, 106, 105, 104, 103, 102, 101, 100, 99},
  {88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98},
  {87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77},
  {66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76},
  {65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55},
  {44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54},
  {43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33},
  {22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32},
  {21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11},
  {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
};

unsigned char matrixValue[MATRIX_HEIGHT][MATRIX_WIDTH];
unsigned char line[MATRIX_WIDTH];
int pcnt = 0;

//Converts an HSV color to RGB color
void HSVtoRGB(void *vRGB, void *vHSV) 
{
  float r, g, b, h, s, v; //this function works with floats between 0 and 1
  float f, p, q, t;
  int i;
  ColorRGB *colorRGB=(ColorRGB *)vRGB;
  ColorHSV *colorHSV=(ColorHSV *)vHSV;

  h = (float)(colorHSV->h / 256.0);
  s = (float)(colorHSV->s / 256.0);
  v = (float)(colorHSV->v / 256.0);

  //if saturation is 0, the color is a shade of grey
  if(s == 0.0) {
    b = v;
    g = b;
    r = g;
  }
  //if saturation > 0, more complex calculations are needed
  else
  {
    h *= 6.0; //to bring hue to a number between 0 and 6, better for the calculations
    i = (int)(floor(h)); //e.g. 2.7 becomes 2 and 3.01 becomes 3 or 4.9999 becomes 4
    f = h - i;//the fractional part of h

    p = (float)(v * (1.0 - s));
    q = (float)(v * (1.0 - (s * f)));
    t = (float)(v * (1.0 - (s * (1.0 - f))));

    switch(i)
    {
      case 0: r=v; g=t; b=p; break;
      case 1: r=q; g=v; b=p; break;
      case 2: r=p; g=v; b=t; break;
      case 3: r=p; g=q; b=v; break;
      case 4: r=t; g=p; b=v; break;
      case 5: r=v; g=p; b=q; break;
      default: r = g = b = 0; break;
    }
  }
  colorRGB->r = (int)(r * 255.0);
  colorRGB->g = (int)(g * 255.0);
  colorRGB->b = (int)(b * 255.0);
}
unsigned char reduce = 4; // used to reduce brightness

void setPixel(unsigned char x, unsigned char y, unsigned char colorR, unsigned char colorG, unsigned char colorB){
  pixels.setPixelColor(mapMatrix[y][x], colorR/reduce, 5*colorG/reduce, colorB/reduce);
}

/**
 * Randomly generate the next line (matrix row)
 */
void generateLine(){
  for(uint8_t x=0; x<MATRIX_WIDTH; x++) {
    line[x] = random(64, 255);
  }
}

/**
 * shift all values in the matrix up one row
 */
void shiftUp() {
  for (uint8_t y=MATRIX_HEIGHT-1; y>0; y--) {
    for (uint8_t x=0; x<MATRIX_WIDTH; x++) {
      matrixValue[y][x] = matrixValue[y-1][x];
    }
  }
  
  for (uint8_t x=0; x<MATRIX_WIDTH; x++) {
    matrixValue[0][x] = line[x];
  }
}

/**
 * draw a frame, interpolating between 2 "key frames"
 * @param pcnt percentage of interpolation
 */
void drawFrame(int pcnt) {
  ColorRGB colorRGB;
  ColorHSV colorHSV;
  int nextv;
  
  //each row interpolates with the one before it
  for (unsigned char y=MATRIX_HEIGHT-1; y>0; y--) {
    for (unsigned char x=0; x<MATRIX_WIDTH; x++) {
        colorHSV.h = hueMask[y][x];
        colorHSV.s = 255;
        nextv = (((100.0-pcnt)*matrixValue[y][x] + pcnt*matrixValue[y][x-1])/100.0) - valueMask[y][x];
        colorHSV.v = (unsigned char) _max(0, nextv);
        
        HSVtoRGB(&colorRGB, &colorHSV);
        setPixel(x, y, colorRGB.r, colorRGB.g, colorRGB.b);
    }
  }
        
  //first row interpolates with the "next" line
  for(unsigned char x=0;x<MATRIX_WIDTH;x++) {
      colorHSV.h = hueMask[0][x];
      colorHSV.s = 255;
      colorHSV.v = (unsigned char)(((100.0-pcnt)*matrixValue[0][x] + pcnt*line[x])/100.0);
      
      HSVtoRGB(&colorRGB, &colorHSV);
      setPixel(x, 0, colorRGB.r, colorRGB.g, colorRGB.b);
  }
  pixels.show();
}

void pixelsFireSetup() {
  randomSeed(analogRead(0));
  generateLine();
  //init all pixels to zero
  memset(matrixValue, 0, sizeof(matrixValue));
}

void loopPixelsFire() {
  pixels.setPixelColor(113, 0);
  pixels.setPixelColor(112, 0);
  pixels.setPixelColor(111, 0);
  pixels.setPixelColor(110, 0);
  if (pcnt >= 100) {
    shiftUp();
    generateLine();
    pcnt = 0;
  }
  drawFrame(pcnt);
  pixels.show();
  pcnt+=20;
}
