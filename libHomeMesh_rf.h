#ifndef LIBHOMEMESH_RF
#define LIBHOMEMESH_RF
//id: the value to encode in the ID field
//payload: the value to encode in the data field
//duration: the number of milliseconds to transmit for
void transmitCommand(int id, int payload, unsigned int duration);
#endif //LIBHOMEMESH_RF
