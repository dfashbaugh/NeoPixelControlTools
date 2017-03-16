boolean useHeartbeat = true;
boolean light = false;

// Uncomment this line if you want to debug
//#define RUN_DEBUG 1
unsigned long debugTimer = 0;
// #define BACKLEDS 369
#define BACKLEDS 372
// #define NUM_STRIPS 3
#define NUM_LEDS_PER_STRIP 100
#define TRUE_NUM_LEDS_PER_STRIP 232

const int totalLEDs = BACKLEDS;

CRGB leds[totalLEDs];

#define READBUFFERSIZE 144

float mIndBrightness = 1.0;
byte mRed1       = 0;
byte mGreen1     = 0;
byte mBlue1      = 0;
byte mPattern    = 0;
byte mRate       = 60;
byte mMapping    = 0;
byte mRed2       = 0;
byte mGreen2     = 0;
byte mBlue2      = 0;

int  mCurrentFrameCount = 0;

byte lastPattern = 0;

#define NUM_STEPS_PER_FRAME 20
#define NULL_PATTERN 0
#define OFF_PATTERN 68
#define PAUSE_PATTERN 67
#define ADV_PATTERN 101
#define RESET_FRAME 100

#define TIMING_ADDR 100

#define MAX_FRAME 2000000


unsigned int rate;
unsigned int patternByte = NULL_PATTERN;

uint8_t r1 = 0, g1 = 0, b1 = 0,
        r2 = 0, g2 = 0, b2 = 0;

uint8_t r3 = 0, g3 = 0, b3 = 0,
        r4 = 0, g4 = 0, b4 = 0;


float params[20];
uint32_t color1, color2, color3 = 0;

boolean isOff = false;

long frame = 1000000;
long lastFrame = -1;

typedef uint32_t (*Pattern)(long, int);

Pattern patterns[128];
Pattern pattern;

typedef int (*Mapping)(long, int);

Mapping mapping;
