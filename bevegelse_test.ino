#include <TheThingsNetwork.h>
 
const char *appEui = "70B3D57ED00132AF";
const char *appKey = "B48CDAA9C9DDF039E95984011FD7C308";
   
#define loraSerial Serial1
#define debugSerial Serial
#define freqPlan TTN_FP_EU868

#include <Wire.h>
#include <Adafruit_AMG88xx.h>

Adafruit_AMG88xx amg;

float pixels[AMG88xx_PIXEL_ARRAY_SIZE];
int rasPyPin = 12;
int ledPin = 13;

TheThingsNetwork ttn(loraSerial, debugSerial, freqPlan);

void setup() {

    pinMode(rasPyPin, OUTPUT);
    pinMode(ledPin, OUTPUT);
    
    loraSerial.begin(57600);
    debugSerial.begin(9600);
    
    // Wait a maximum of 10s for Serial Monitor
    while (!debugSerial && millis() < 10000);
    
    debugSerial.println("-- STATUS");
    ttn.showStatus();

    debugSerial.println("-- JOIN");
    ttn.join(appEui, appKey);

    
    debugSerial.println(F("AMG88xx pixels"));

    bool status;
    
    // default settings
    status = amg.begin();
    if (!status) {
        debugSerial.println("Could not find a valid AMG88xx sensor, check wiring!");
        while (1);
    }
    
    debugSerial.println("-- Pixels Test --");

    debugSerial.println();

    delay(100); // let sensor boot up
}


void loop() { 

    byte data[1];
    data[0] = 1;
    
    //read all the pixels
    amg.readPixels(pixels);


    for(int i=1; i<=64; i++){
      
      if (pixels[i-1] >= 26) {
        digitalWrite(rasPyPin, HIGH);
        delay(10);
        digitalWrite(rasPyPin, LOW);
        digitalWrite(ledPin, HIGH);
        delay(10);
        digitalWrite(ledPin, LOW);
        // Send it off
        //ttn.sendBytes(data, sizeof(data));
        Serial.println(1);
        break;
      }
      
    }
    
    //delay
    delay(5000);
}
