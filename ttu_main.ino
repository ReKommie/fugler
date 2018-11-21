#include <TheThingsNetwork.h>
#include <Wire.h>
#include <Adafruit_AMG88xx.h>


//The Things Network:
const char *appEui = "70B3D57ED00132AF";
const char *appKey = "B48CDAA9C9DDF039E95984011FD7C308";
   
#define loraSerial Serial1
#define freqPlan TTN_FP_EU868
TheThingsNetwork ttn(loraSerial, Serial, freqPlan);

//Sensor
Adafruit_AMG88xx amg;
float pixels[AMG88xx_PIXEL_ARRAY_SIZE];
int numPixls;

void setup() {
  loraSerial.begin(57600);
  Serial.begin(9600);

//Starter TTN forbindelse:
  //Wait a maximum of 10s for Serial Monitor
  while (!Serial && millis() < 10000);
    
  Serial.println("-- STATUS");
  ttn.showStatus();

  Serial.println("-- JOIN");
  ttn.join(appEui, appKey);

//Starter sensoren:
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
      if (pixels[i-1] >= 20) { //Avgjør om en piksel er utløst
        ++numPixls; 
      }
    }

    if (numPixls > 10) { //mimum 10 piksler for at sensoren skal utløses
      Serial.println("Cheeeeeese"); //dette får Raspberry Pi til å ta bilde
      ttn.sendBytes(data, sizeof(data)); //Sender datapakke til nettsiden
      delay(4000);
    }
    
    numPixls = 0;
    
    //delay
    delay(5);
 
}
