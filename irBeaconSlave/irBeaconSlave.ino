
#include <Manchester.h>

/*

  Manchester Receiver example
  
  In this example receiver will receive one byte of payoad and 4 bit sender id per transmittion
  message also contains a checksum and receiver can check if the data has been transmited correctly

  try different speeds using this constants, your maximum possible speed will 
  depend on various factors like transmitter type, distance, microcontroller speed, ...

  MAN_300 0
  MAN_600 1
  MAN_1200 2
  MAN_2400 3
  MAN_4800 4
  MAN_9600 5
  MAN_19200 6
  MAN_38400 7


*/

#define RX_PIN 0
#define LED_PIN 13
#define IR_LED_PIN 7
#define MSG_ID_SET_DURATION 0
#define MSG_ID_ACTIVATE_SLAVE 1
#define SLAVE_ID 1

uint8_t data;
uint8_t id;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(IR_LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, 1);
  digitalWrite(IR_LED_PIN,1);
  delay(1000);
  digitalWrite(LED_PIN, 0);
  digitalWrite(IR_LED_PIN,0);
  Serial.begin(9600);
  
  man.setupReceive(RX_PIN, MAN_1200);
  man.beginReceive();
}

int duration = 16;
int pinOnTime = 0;
bool irLedOn = false;

void loop() {
  if (man.receiveComplete()) { //received something
  Serial.print("Receive complete\n");
    uint16_t m = man.getMessage();
    man.beginReceive(); //start listening for next message right after you retrieve the message
    if (man.decodeMessage(m, id, data)) { //extract id and data from message, check if checksum is correct
      
      //check the message type
      switch(id) {
        case MSG_ID_SET_DURATION:
            duration = data;
            Serial.print("New duration set to ");
            Serial.print(duration);
            Serial.println();
        break;
        case MSG_ID_ACTIVATE_SLAVE:
            Serial.print("Received slave activate message with ID ");
            Serial.print(data);
            if (data == SLAVE_ID) {
                //turn on my IR LED for duration/255 seconds
                pinOnTime = millis();
                irLedOn = true;
                digitalWrite(IR_LED_PIN, 1);
                digitalWrite(LED_PIN, 1);
                
            }
        break;
        default:
        break;  
      }
    }
  }
  if(irLedOn && (millis() - pinOnTime > ((float)duration/255.0)*1000.0)) {
      //turn off the pin and reset the timer
      digitalWrite(IR_LED_PIN, 0);
      digitalWrite(LED_PIN, 0);
      irLedOn = false;
  }
}

