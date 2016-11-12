#include <FastLED.h>
#include <Ethernet.h> 
#include <EthernetUdp.h> 
#include <SPI.h> 

// An EthernetUDP instance to let us send and receive packets over UDP
EthernetUDP Udp;

boolean debug = 1; //activate serial printing, !! waits for a serial input to start loop

#define NUM_LEDS 640
#define MEMORY_SIZE NUM_LEDS*3

byte drawingMemory[MEMORY_SIZE];

CRGB leds1[64];
CRGB leds2[64];
CRGB leds3[64];
CRGB leds4[64];
CRGB leds5[64];
CRGB leds6[64];
CRGB leds7[128];
CRGB leds8[128];

long memoryCounter = 0;

// buffers for receiving and sending data
char packetBuffer[2000]; //buffer to hold incoming packet,

// Change ip and mac address for your setup
byte ip[] = {192,168,2,2};
char mac_string[20];

unsigned int localPort = 8888; // local port to listen on

//everything on the network needs a unique MAC

#if defined(__MK20DX128__) || defined(__MK20DX256__)
    // Teensy 3.x has MAC burned in
static byte mac[6];
void read(uint8_t word, uint8_t * mac, uint8_t offset) {
    FTFL_FCCOB0 = 0x41; // Selects the READONCE command
    FTFL_FCCOB1 = word; // read the given word of read once area

    // launch command and wait until complete
    FTFL_FSTAT = FTFL_FSTAT_CCIF;
    while (!(FTFL_FSTAT & FTFL_FSTAT_CCIF));

    *
    (mac + offset) = FTFL_FCCOB5; // collect only the top three bytes,
    *
    (mac + offset + 1) = FTFL_FCCOB6; // in the right orientation (big endian).
    *
    (mac + offset + 2) = FTFL_FCCOB7; // Skip FTFL_FCCOB4 as it's always 0.
}
void read_mac() {
    read(0xe, mac, 0);
    read(0xf, mac, 3);
}
#else
    void read_mac() {}
byte mac[] = {
    0xDE,
    0xAD,
    0xBE,
    0xEF,
    0xFE,
    0xED
}; // you can find this written on the board of some Arduino Ethernets or shields

#endif

void print_mac() {
    size_t count = 0;
    for (uint8_t i = 0; i < 6; ++i) {
        if (i != 0) count += Serial.print(":");
        count += Serial.print(( * (mac + i) & 0xF0) >> 4, 16);
        count += Serial.print( * (mac + i) & 0x0F, 16);
    }
    sprintf(mac_string, "%02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    Serial.println();
}

void setup() {
        Ethernet.begin(mac, ip);
        Udp.begin(localPort);

        FastLED.addLeds<WS2812B,  2, GRB>(leds1, 64);
        FastLED.addLeds<WS2812B, 14, GRB>(leds2, 64);
        FastLED.addLeds<WS2812B,  7, GRB>(leds3, 64);
        FastLED.addLeds<WS2812B,  8, GRB>(leds4, 64);
        FastLED.addLeds<WS2812B,  6, GRB>(leds5, 64);
        FastLED.addLeds<WS2812B, 20, GRB>(leds6, 64);
        FastLED.addLeds<WS2812B, 21, GRB>(leds7, 128);
        FastLED.addLeds<WS2812B,  5, GRB>(leds8, 128);
        FastLED.show();

        read_mac();
        if (debug) {
            Serial.begin(9600);

            delay(1000);
            // while (!Serial) {;
            // } //if debug, wait until you send something to start the sketch

            Serial.print("mac : ");

            print_mac();

            Serial.print("IP : ");

            for (int i = 0; i < 3; i++) {
                Serial.print(ip[i]);
                Serial.print(".");
            }

            Serial.println(ip[3]);

        }
}

void loop() {
    int packetSize = Udp.parsePacket();
    if (packetSize) {

        Udp.read(packetBuffer, 2000);

        if(packetBuffer[0] == 'o' && packetBuffer[1] == 'n')
        {
            for(int i = 0; i < packetSize/3; i++)
            {
                CRGB myColor;
                myColor.green = packetBuffer[i*3 + 2];
                myColor.red = packetBuffer[i*3+1 + 2];
                myColor.blue = packetBuffer[i*3+2 + 2];

                myColor.green = map(myColor.green, 0, 255, 0, 128);
                myColor.red = map(myColor.red, 0, 255, 0, 128);
                myColor.blue = map(myColor.blue, 0, 255, 0, 128);
    
                if(i < 64) // Strip 1
                    leds1[63 - i] = myColor;
                else if(i < 128) // Strip 2
                    leds2[63 - i%64] = myColor;
                else if(i < 192) // Strip 3
                    leds3[63 - i%64] = myColor;
                else if(i < 256) // Strip 4
                    leds4[63 - i%64] = myColor;
                else if(i < 320) // Strip 5
                    leds5[63 - i%64] = myColor;
                else if(i < 384) // Strip 6
                    leds6[63 - i%64] = myColor;
                else if(i < 512) // Strip 7
                    leds7[i%128] = myColor;
                else if(i < 640) // Strip 8
                    leds8[i%128] = myColor;
            }   
        }
        else if(packetBuffer[0] == 't' && packetBuffer[1] == 'w')
        {
            for(int i = 0; i < packetSize/3; i++)
            {
                int LED = i+300;

                CRGB myColor;
                myColor.green = packetBuffer[i*3 + 2];
                myColor.red = packetBuffer[i*3+1 + 2];
                myColor.blue = packetBuffer[i*3+2 + 2];

                myColor.green = map(myColor.green, 0, 255, 0, 128);
                myColor.red = map(myColor.red, 0, 255, 0, 128);
                myColor.blue = map(myColor.blue, 0, 255, 0, 128);
    
                if(LED < 64) // Strip 1
                    leds1[LED] = myColor;
                else if(LED < 128) // Strip 2
                    leds2[LED%64] = myColor;
                else if(LED < 192) // Strip 3
                    leds3[LED%64] = myColor;
                else if(LED < 256) // Strip 4
                    leds4[LED%64] = myColor;
                else if(LED < 320) // Strip 5
                    leds5[63 - LED%64] = myColor;
                else if(LED < 384) // Strip 6
                    leds6[63 - LED%64] = myColor;
                else if(LED < 512) // Strip 7
                {
                    if(LED < 384+64)
                        leds7[63 - LED%64] = myColor;
                    else 
                        leds7[127 - LED%64] = myColor;
                }
                else if(LED < 640) // Strip 8
                {
                    if(LED < 512+64)
                        leds8[63 - LED%64] = myColor;
                    else 
                        leds8[127 - LED%64] = myColor;
                }
            } 
        }
        

        FastLED.show();
    }
}
