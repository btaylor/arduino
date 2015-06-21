#include <Adafruit_NeoPixel.h>

// IMPORTANT: Set pixel COUNT, PIN and TYPE
#define PIXEL_PIN 2
#define PIXEL_COUNT 4
#define PIXEL_TYPE NEO_GRB + NEO_KHZ800

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

int brightness = 0;
bool dimming = false;
bool latch = false;

void setup() 
{
    pinMode(0, INPUT);
    
    strip.begin();
    strip.show(); // Initialize all pixels to 'off'
}

void loop() 
{
    int capTouch = digitalRead(0);
    if (capTouch == LOW && !latch) {
        if (dimming) {
            brightness -= 10;
        } else {
            brightness += 5;
        }
        
        if (brightness >= 255) {
            brightness = 255;
            latch = true;
            dimming = true;
        } else if (brightness <= 0) {
            brightness = 0;
            latch = true;
            dimming = false;
        }
    } else if (capTouch == HIGH) {
        latch = false;
    }
    
    int r = 255;
    int g = 200;
    int b = 40;

    for(int x = 0; x < PIXEL_COUNT; x++) {
        int flicker = random(0, 150);
        int r1 = r - flicker;
        int g1 = g - flicker;
        int b1 = b - flicker;
        
        if(g1 < 0) g1 = 0;
        if(r1 < 0) r1 = 0;
        if(b1 < 0) b1 = 0;
        
        strip.setPixelColor(x, r1, g1, b1);
    }
    
    strip.setBrightness(brightness);
    strip.show();
    delay(random(10, 300));
}
