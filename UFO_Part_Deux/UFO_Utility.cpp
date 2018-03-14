#include "UFO_Utility.h"

#ifdef PC_DEBUG
void DebugPrint(std::string myString)
{
  cout << myString << endl;
}
#else
void DebugPrint(char* myString)
{
  Serial.println(myString);
}
#endif

#ifndef ARDUINO
  unsigned long milliseconds = 0;
  unsigned long GetMilliseconds() {return milliseconds++;};
#else
  unsigned long GetMilliseconds() {return millis();};
#endif

int lerp(int a, int b, float t) {
  return a + (b - a)*t; 
}

Color lerpColor(Color a, Color b, float t) {
  return Color(lerp(a.Red, b.Red, t), 
  lerp(a.Green, b.Green, t), 
  lerp(a.Blue, b.Blue, t));
}

Color Wheel(int WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}