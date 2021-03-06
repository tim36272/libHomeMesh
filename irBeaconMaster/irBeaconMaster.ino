#include <Manchester.h>

/*

  Manchester Transmitter example
  
  In this example transmitter will send one byte of data and 4bit sender ID per transmittion
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

#define TX_PIN 5  //pin where your transmitter is connected
#define LED_PIN 13 //pin for blinking LED
#define MSG_ID_SET_DURATION 0
#define MSG_ID_ACTIVATE_SLAVE 1
#define SLAVE_DURATION 32 //this is a the duration, as a ratio of 255, of the fraction of a second to keep the transmitter on. For example, 32 means keep the light on for 32/255 of a second

uint8_t transmit_data = 0;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, 0);
  man.workAround1MhzTinyCore(); //add this in order for transmitter to work with 1Mhz Attiny85/84
  man.setupTransmit(TX_PIN, MAN_1200);
  Serial.begin(9600);
  //set the transmission duration
  man.transmit(man.encodeMessage(MSG_ID_SET_DURATION, SLAVE_DURATION));
}

uint8_t duration = 128;

void loop() {
    //wait for a serial message
    while (true) {
        int requestedSlave = Serial.parseInt();
        delay(1000);
        requestedSlave = 1;
        if(requestedSlave == 0) {
          continue;
        }
        if(requestedSlave == 255) {
          //this is actually a change duration request, so get the duration
          uint8_t newDuration = Serial.parseInt();
          if(newDuration > 0) {
            duration = newDuration;
            Serial.print("New duration set to: ");
            Serial.print(duration);
            Serial.println();
            man.transmit(man.encodeMessage(MSG_ID_SET_DURATION, newDuration));
          }
          continue;
        }
        
        //a new slave is being requested
        Serial.print("Activiting slave ");
        Serial.print(requestedSlave); 
        Serial.println();
        //transmit the slave ID
        man.transmit(man.encodeMessage(MSG_ID_ACTIVATE_SLAVE, requestedSlave));
    }
}
