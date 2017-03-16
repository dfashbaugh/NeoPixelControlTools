//#define USE_OCTOWS2811

#define USE_VDMX

//#define USB_MIDI

//#define USING_ABLETON

// #ifndef USB_MIDI
#include <Arduino.h>
#include <MIDI.h>
// #endif

//#include<OctoWS2811.h>
#include <FastLED.h>
#include "CommonVariables.h"
#include "mappings.h"
#include "utils.h"
#include "patterns.h"

/* Helper functions */

//Input a rateue 0 to 384 to get a color rateue.
//The colours are a transition r - g -b - back to r

int numPatterns = 17;
unsigned int mPattern_to_patternByte(byte incomingByte)
{
  switch (incomingByte) {
    case 0:
      return 68;
      break;
    case 1:
      return 69;
      break;
    case 2:
      return 70;
      break;
    case 3:
      return 62;
      break;
    case 4:
      return 63;
      break;
    case 5:
      return 64;
      break;
    case 6:
      return 65;
      break;
    case 7:
      return 66;
      break;
    case 8:
      return 71;
      break;
    case 9:
      return 72;
      break;
    case 10:
      return 73;
      break;
    case 11:
      return 74;
      break;
    case 12:
      return 75;
      break;
    case 13:
      return 76;
      break;
    case 14:
      return 77;
      break;
    case 15:
      return 78;
      break;
    case 16:
      return 79;
      break;
    case 17:
      return 80;
      break;
    default:
      return 0;
      break;
  }


}

void setColors()
{
  color1 = myColor(r1, g1, b1);
  color2 = myColor(r2, g2, b2);
}

void hideAll() {
  for (int i = 0; i < totalLEDs; i++) {
    leds[i] = CRGB(0, 0, 0);
  }
}

void showAll() {
  LEDS.show();
}


void ledCheck(){

  for (int f = 255; f >= 0; f-=3){
      for(int i = 0; i < totalLEDs; i++){
            leds[i] = CRGB(f,f,f);
      }
      LEDS.show();
      // delay(1);
  }

}

byte DecodeVDMXPattern(int value)
{
  int numIncrement = 127/numPatterns;

  for(int i = 0; i < numPatterns; i++)
  {
    if(i*numIncrement <= value && (i+1)*numIncrement > value)
    {
      return i;
    }
  }
  return 0;
}

void SetNewMapping(int value)
{
  if(value == 0)
  {
    mapping = &forward;
  }
  else if(value == 1)
  {
    mapping = &backward;
  }
  else if(value == 2)
  {
    mapping = &snake;
  }
  else if(value == 3)
  {
    mapping = &intoSpace;
  }
  else if(value == 4)
  {
    mapping = &shortSnake;
  }
  else if(value == 5)
  {
    mapping = &longSnake;
  }
  else if(value == 6)
  {
    mapping = &dekonstruktor;
  }
  else if(value == 7)
  {
    mapping = &dekonstruktorIntoSpace;
  }
  else if(value == 8)
  {
    mapping = &horizontal;
  }
  else if(value == 9)
  {
    mapping = &vertical;
  }
  else if(value == 10)
  {
    mapping = &dekonstruktorHorizontal;
  }
  else if(value >= 11)
  {
    mapping = &dekonstrucktorVertical;
  }
  //else if(value == 7)
  //{
  //  mapping = &dekonstruktorRando;
  //}
}

enum controlEnum{setBrightness = 0, setRed1 = 1, setGreen1 = 2, setBlue1 = 3, setPattern = 4, 
                 setRate = 5, setMapping = 6, setRed2 = 7, setGreen2 = 8, setBlue2 = 9};
void OnControlChange(byte channel, byte control, byte value) {
  
  // Serial.print(channel);
  // Serial.print("\t");
  // Serial.print(control);
  // Serial.print("\t");
  // Serial.println(value);
  #ifdef USING_ABLETON
    if (control >= 1) control--;
  #endif

  boolean colorChanged = false;

  if(control == setBrightness)
  {
    mIndBrightness = ((float)value) / 127.0;
  }
  else if(control == setRed1)
  {
    r1 = map(value, 0, 127, 0, 255);
    colorChanged = true;
  }
  else if(control == setGreen1)
  {
    g1 = map(value, 0, 127, 0, 255);
    colorChanged = true;
  }
  else if(control == setBlue1)
  {
    b1 = map(value, 0, 127, 0 ,255);
    colorChanged = true;
  }
  else if(control == setPattern)
  {

    #ifdef USE_VDMX
      patternByte = mPattern_to_patternByte(DecodeVDMXPattern(value));
    #else
      patternByte = mPattern_to_patternByte(value);
    #endif

    if (patternByte != NULL_PATTERN && patterns[patternByte] != NULL) {
      isOff = false;
      pattern = patterns[patternByte];
      pattern(-2, 0); // On select initialization
    }
    // Reset frame if pattern change
    if(patternByte != lastPattern)
    {
      lastPattern = patternByte;
      frame = 1000000;
    }

  }
  else if(control == setRate)
  {
    rate = map(value, 0, 127, 0, 255);
  }
  else if(control == setMapping)
  {
    SetNewMapping(value);
  }
  else if(control == setRed2)
  {
    r2 = map(value, 0, 127, 0, 255);
    colorChanged = true;
  }
  else if(control == setGreen2)
  {
    g2 = map(value, 0, 127, 0, 255);
    colorChanged = true;
  }
  else if(control == setBlue2)
  {
    b2 = map(value, 0, 127, 0, 255);
    colorChanged = true;
  }

  if(colorChanged)
  {
    setColors();
  }

}

byte currentCommandBuf [READBUFFERSIZE];

bool TOGGLE1 = true;
bool TOGGLE2 = true;
bool TOGGLE3 = true;
bool TOGGLE4 = true;
bool TOGGLE5 = true;
bool MASTERTOGGLE = true;


bool FREESTYLETOGGLE = false;

void HandleNoteOn (byte channel, byte pitch, byte velocity) {

  // Serial.print(channel);
  // Serial.print("\t");
  // Serial.print(pitch);
  // Serial.print("\t");
  // Serial.println(velocity);

  if (velocity == 0) { // note off keeps LEDs on
    if(pitch == 60) TOGGLE1 = true;
    else if(pitch == 61) TOGGLE2 = true;
    else if(pitch == 62) TOGGLE3 = true;
    else if(pitch == 63) TOGGLE4 = true;
    else if(pitch == 64) TOGGLE5 = true;

    else if(pitch == 81) TOGGLE1 = true;
    else if(pitch == 76) TOGGLE2 = true;
    else if(pitch == 74) TOGGLE3 = true;
    else if(pitch == 69) TOGGLE4 = true;
    else if(pitch == 57) TOGGLE5 = true;

  }
  else{
    if(pitch == 60) TOGGLE1 = false;
    else if(pitch == 61) TOGGLE2 = false;
    else if(pitch == 62) TOGGLE3 = false;
    else if(pitch == 63) TOGGLE4 = false;
    else if(pitch == 64) TOGGLE5 = false;


    else if(pitch == 81) TOGGLE1 = false;
    else if(pitch == 76) TOGGLE2 = false;
    else if(pitch == 74) TOGGLE3 = false;
    else if(pitch == 69) TOGGLE4 = false;
    else if(pitch == 57) TOGGLE5 = false;

    if(pitch == 72) {
      MASTERTOGGLE = true;
      FREESTYLETOGGLE = false;
    }
    else if(pitch == 73) {
      MASTERTOGGLE = false;
      FREESTYLETOGGLE = false;
    }
    if(pitch == 74) FREESTYLETOGGLE = true;
  }
}

void HandleNoteOff (byte channel, byte pitch, byte velocity) {

  // Serial.print(channel);
  // Serial.print("\t");
  // Serial.print(pitch);
  // Serial.print("\t");
  // Serial.println(velocity);

  if(pitch == 60) TOGGLE1 = true;
  else if(pitch == 61) TOGGLE2 = true;
  else if(pitch == 62) TOGGLE3 = true;
  else if(pitch == 63) TOGGLE4 = true;
  else if(pitch == 64) TOGGLE5 = true;


  else if(pitch == 81) TOGGLE1 = true;
  else if(pitch == 76) TOGGLE2 = true;
  else if(pitch == 74) TOGGLE3 = true;
  else if(pitch == 69) TOGGLE4 = true;
  else if(pitch == 57) TOGGLE5 = true;

}

void setup() {

  pinMode(13, OUTPUT);
  // Serial.begin(115200);

//  LEDS.addLeds<OCTOWS2811>(leds, NUM_LEDS_PER_STRIP).setCorrection( 0x9FFAF0 );
  // FastLED.addLeds<WS2811, 17, GRB>(leds, 0,BACKLEDS).setCorrection( 0x9FFAF0 );
  FastLED.addLeds<WS2811, 17, GRB>(leds, 0,BACKLEDS).setCorrection( 0x9FFAF0 );

  LEDS.setBrightness(255);

  ledCheck();

  setColors();

  hideAll();
  showAll();

  patterns[62] = &flickerStrobeTwo;
  patterns[63] = &flickerStrobeFour;
  patterns[64] = &totesRandom;
  patterns[65] = &rainbowCycle;
  patterns[66] = &rainbow;
  // 67 = pause
  // 68 = off
  patterns[69] = &solidColor;
  patterns[70] = &gradient;
  patterns[71] = &pulseSine;
  patterns[72] = &pulseSaw;
  patterns[73] = &bounce;
  patterns[74] = &colorWipe;
  patterns[75] = &colorAlternator;
  patterns[76] = &stripe;
  patterns[77] = &colorChase;
  patterns[78] = &colorWipeMeter;
  patterns[79] = &colorWipeMeterGradient;
  patterns[80] = &pulseOnce;

  rate = 122;
  // pattern = &pulseOnce;
  pattern = &solidColor;
  mapping = &forward;

  mIndBrightness = 255;
  
  rate = mRate + 1;
  
  // #ifdef USB_MIDI
  usbMIDI.setHandleControlChange(OnControlChange);
  usbMIDI.setHandleNoteOn(HandleNoteOn);
  usbMIDI.setHandleNoteOff(HandleNoteOff);
  // #else
  // MIDI.begin(MIDI_CHANNEL_OMNI);  
  // MIDI.begin(7);    
  // MIDI.setHandleControlChange(OnControlChange);
  // MIDI.setHandleNoteOn(HandleNoteOn);
  // MIDI.setHandleNoteOff(HandleNoteOff);
  // #endif
}

void drawLEDs(){
  int usedRate = 128-rate;
  mCurrentFrameCount += abs(usedRate);
  
  if(mCurrentFrameCount >= NUM_STEPS_PER_FRAME)
  {
    int framesToMove = mCurrentFrameCount/NUM_STEPS_PER_FRAME;
    mCurrentFrameCount = mCurrentFrameCount - framesToMove*NUM_STEPS_PER_FRAME;
    
    frame += usedRate < 0 ? -1*framesToMove : framesToMove;  
  }

  if (frame != lastFrame)
    pattern(-1, 0); // Per frame initialization

  lastFrame = frame;

  for (int i = 0; i < totalLEDs; i++) {


    if(!FREESTYLETOGGLE){
      if(!TOGGLE1 && ( i >= 0 && i < 44 ) ) leds[i] = CRGB(0,0,0);
      else if(!TOGGLE2 && ( i >= 44 && i < 73 ) ) leds[i] = CRGB(0,0,0);
      else if(!TOGGLE3 && ( i >= 73 && i < 111 ) ) leds[i] = CRGB(0,0,0);
      else if(!TOGGLE4 && ( i >= 111 && i < 140 ) ) leds[i] = CRGB(0,0,0);
      else if(!TOGGLE5 && ( i >= 140 && i < 184 ) ) leds[i] = CRGB(0,0,0);
      else{
        int j = mapping(frame, i);
        uint32_t color = pattern(frame, j);

        uint8_t r = ((color & 0xFF0000) >> 16);
        uint8_t g = ((color & 0x00FF00) >> 8);
        uint8_t b = ((color & 0x0000FF));

        //TODO change setbrightness only on change
        if (mIndBrightness < 1.0) {
          r *= mIndBrightness;
          g *= mIndBrightness;
          b *= mIndBrightness;
        }

        // float whiteDimmer = 0.7;

        // if (r == g && g == b) {
        //   r *= whiteDimmer;
        //   g *= whiteDimmer;
        //   b *= whiteDimmer;
        // }

        leds[i] = CRGB(r, g, b); 
      }
    }
    else{
      if(TOGGLE1 && ( i >= 0 && i < 44 ) ) leds[i] = CRGB(0,0,0);
      else if(TOGGLE2 && ( i >= 44 && i < 73 ) ) leds[i] = CRGB(0,0,0);
      else if(TOGGLE3 && ( i >= 73 && i < 111 ) ) leds[i] = CRGB(0,0,0);
      else if(TOGGLE4 && ( i >= 111 && i < 140 ) ) leds[i] = CRGB(0,0,0);
      else if(TOGGLE5 && ( i >= 140 && i < 184 ) ) leds[i] = CRGB(0,0,0);
      else{
        int j = mapping(frame, i);
        uint32_t color = pattern(frame, j);

        uint8_t r = ((color & 0xFF0000) >> 16);
        uint8_t g = ((color & 0x00FF00) >> 8);
        uint8_t b = ((color & 0x0000FF));

        //TODO change setbrightness only on change
        if (mIndBrightness < 1.0) {
          r *= mIndBrightness;
          g *= mIndBrightness;
          b *= mIndBrightness;
        }

        // float whiteDimmer = 0.7;

        // if (r == g && g == b) {
        //   r *= whiteDimmer;
        //   g *= whiteDimmer;
        //   b *= whiteDimmer;
        // }

        leds[i] = CRGB(r, g, b); 
      }

    }

  }

  if (isOff || !MASTERTOGGLE) {
    hideAll();
  }

  showAll();

  if (frame >= MAX_FRAME) {
    frame = 0;
  }

  /*
  if (light)
    digitalWrite(13, HIGH);
  else
    digitalWrite(13, LOW);

  light = !light;
  */
}

int _interval = 33;
unsigned long curTime;
unsigned long lastMillis;

void loop() {
  // #ifdef USB_MIDI 
  usbMIDI.read();
  // #else
  // MIDI.read();
  // #endif
  curTime = millis();

  if(curTime > lastMillis + _interval){  
    drawLEDs();
    lastMillis = curTime;
  }


  

}

