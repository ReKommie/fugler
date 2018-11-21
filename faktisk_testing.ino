#include <Wire.h>
#include <Adafruit_AMG88xx.h>

Adafruit_AMG88xx amg;
float pixels[AMG88xx_PIXEL_ARRAY_SIZE];
int numPixls;

void setup() {
  
  Serial.begin(9600);
 
  Serial.println(F("AMG88xx pixels"));

  bool status;
    
  // default settings
  status = amg.begin();
  if (!status) {
      Serial.println("Could not find a valid AMG88xx sensor, check wiring!");
      while (1);
  }

    delay(1000); // let sensor boot up
}

void loop() {

    //Prepare array of 1 byte to indicate movement
    byte data[1];
    data[0] = 1;

    //read all the pixels
    amg.readPixels(pixels);
    for(int i=1; i<=64; i++){ //itererer gjennom pikslene
      if (pixels[i-1] >= 20) {
        Serial.println(1);
      }
    }
    Serial.println(0);

    
    //delay
 
}
