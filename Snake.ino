class Coord {
  public:
    Coord() {
      x = 255;
      y = 255;
    }
    Coord(byte pX, byte pY) {
      x = pX;
      y = pY;
    }
    byte x;
    byte y;
};

byte snakeDirection = 0, snakeLength = 1; // 0 = up, 1 = right, 2 = bottom, 3 = left
Coord snakePosition, foodPosition;
Coord * snakeSegments = new Coord[110];

void snakeSetup() {
  snakeReset();
}

void snakeLoop() {
  
}

void snakeReset() {
  snakeDirection = 0;
  snakeLength = 1;
  snakePosition.x = 0;
  snakePosition.y = 9;
  snakeSegments[0].x = snakePosition.x;
  snakeSegments[0].y = snakePosition.y;
}

void spawnFood() {
  byte x, y;

  // Yes! This is the first time I actually use a do {} while (); loop!
  do {
    x = random(10);
    y = random(9);
  } 
  while (segmentExists(x, y));
  foodPosition.x = x;
  foodPosition.y = y;
}

boolean segmentExists(byte x, byte y) {
  for (int i = 0; i < snakeLength; i++) {
    if (snakeSegments[i].x == x && snakeSegments[i].y == y) {
      return true;
    }
    return false;
  }
}

void addNewSegment() {
  snakeSegments[snakeLength].x = snakePosition.x;
  snakeSegments[snakeLength].y = snakePosition.y;

  snakeLength++;
}

