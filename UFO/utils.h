uint8_t red(uint32_t c) {
  return ((c & 0xFF0000) >> 16);
}
uint8_t green(uint32_t c) {
  return ((c & 0x00FF00) >> 8);
}
uint8_t blue(uint32_t c) {
  return (c & 0x0000FF);
}

byte lerp(byte a, byte b, float t) {
  return a + (b - a)*t; 
}

uint32_t myColor(uint8_t r , uint8_t g , uint8_t b){
  return ((uint32_t)(r) << 16) | ((uint32_t)(g ) <<  8) | (b );
}

uint32_t lerpColor(uint32_t a, uint32_t b, float t) {
  return myColor(lerp(red(a), red(b), t), 
  lerp(green(a), green(b), t), 
  lerp(blue(a), blue(b), t));
}

float triangleWave(int frame, float rate) {
  if ((int)(frame / rate) % 2 == 0) {
    return (frame % (int)rate / rate);
  } 
  else { 
    return 1 - (frame % (int)rate / rate);
  }
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return myColor(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return myColor(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return myColor(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}
