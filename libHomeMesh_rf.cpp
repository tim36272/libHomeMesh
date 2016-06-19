#include "libHomeMesh_rf.h"
#include <libHomeMesh_util.h>
#include <Manchester.h>
//id: the value to encode in the ID field
//payload: the value to encode in the data field
//duration: the number of milliseconds to transmit for
void transmitCommand(int id, int payload, unsigned int duration) {
  blinkAcknowledge(13, 200);
  uint8_t i;
  //each transmission takes about 99 ms, so run the command duration/100 times
  for (i=0;i<duration/100;i++) {
    man.transmit(man.encodeMessage(id, payload));
  }
  //signal that the command worked
  blinkAcknowledge(13, 1000);
}
