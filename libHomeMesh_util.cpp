#include "libHomeMesh_util.h"
//pin: the pin to blink
//duration: in millisecons
void blinkAcknowledge(uint8_t pin, uint8_t duration) {
  //blink the light and at the same time block further commands for six seconds since the transmitter may retransmit the same message many times
  uint8_t i;
  for (i = 0; i < (duration / 200); i++) { 
    digitalWrite(pin,1);
    delay(100);
    digitalWrite(pin,0);
    delay(100);
  }
}
