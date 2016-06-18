#include "libHomeMesh_rf.h"
//id: the value to encode in the ID field
//payload: the value to encode in the data field
//duration: the number of milliseconds to transmit for
void transmitCommand(int id, int payload, unsigned int duration) {
  acknowledge(200);
  uint8_t i;
  //each transmission takes about 99 ms, so run the command duration/100 times
  for (i=0;i<duration/100;i++) {
    man.transmit(man.encodeMessage(id, payload));
  }
  //signal that the command worked
  acknowledge(1000);
}
