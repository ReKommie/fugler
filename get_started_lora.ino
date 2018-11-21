#include <TheThingsNetwork.h>
 
const char *appEui = "70B3D57ED00132AF";
const char *appKey = "B48CDAA9C9DDF039E95984011FD7C308";
   
#define loraSerial Serial1
#define debugSerial Serial
#define freqPlan TTN_FP_EU868


int buttonPin = 3;    //the digital pin connected to button intput
int ledPin = 13;
int buttonPin2 = 2;

TheThingsNetwork ttn(loraSerial, debugSerial, freqPlan);
    
void setup() {
  loraSerial.begin(57600);
  debugSerial.begin(9600);
      
  // Initialize LED output pin
  pinMode(ledPin, OUTPUT);
  // Inizialize BUTTON input pin
  pinMode(buttonPin, INPUT);
  pinMode(buttonPin, INPUT);
    
  // Wait a maximum of 10s for Serial Monitor
  while (!debugSerial && millis() < 10000);
    
  debugSerial.println("-- STATUS");
  ttn.showStatus();

  debugSerial.println("-- JOIN");
  ttn.join(appEui, appKey);

  // Set callback for incoming messages
  ttn.onMessage(message);

  delay(1000);

}

void loop() {
  
       
  // Prepare array of 1 byte to indicate LED status
  byte data[3];
  data[0] = (digitalRead(buttonPin) == HIGH) ? 1 : 0;;
  data[1] = (digitalRead(buttonPin2) == HIGH) ? 1 : 0;;
  data[2] = (digitalRead(ledPin) == HIGH) ? 1 : 0;
  
  ttn.sendBytes(data, sizeof(data));

  delay(4000);
}

void message(const byte* payload, size_t length, port_t port) {
  debugSerial.println("-- MESSAGE");
    
  // Only handle messages of a single byte
  if (length != 1) {
    return;
  }
    
  if (payload[0] == 0) {
    debugSerial.println("LED: off");
    digitalWrite(ledPin, LOW);
          
  } else if (payload[0] == 1) {
    debugSerial.println("LED: on");
    digitalWrite(ledPin, HIGH);    
    byte data[3];
    data[0] = (digitalRead(buttonPin) == HIGH) ? 1 : 0;
    data[1] = (digitalRead(buttonPin2) == HIGH) ? 1 : 0;
    data[2] = (digitalRead(ledPin) == HIGH) ? 1 : 0;
 
    // Send it off
    ttn.sendBytes(data, sizeof(data));
  }
}
