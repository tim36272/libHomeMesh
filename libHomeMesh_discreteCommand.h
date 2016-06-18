#ifndef LIBHOMEMESH_DISCRETECOMMAND
#define LIBHOMEMESH_DISCRETECOMMAND

#define STATE_TRANSITION_TIMEOUT 1000

typedef enum {
  DISCRETE_COMMAND_STATE_IDLE,
  DISCRETE_COMMAND_STATE_FIRST_HIGH,
  DISCRETE_COMMAND_STATE_FIRST_LOW,
  DISCRETE_COMMAND_STATE_ENGAGE
}discreteCommandState_t;

//pin: The Arduino pin to check
//state: the current state
//stateTimestamp: the time the state was entered
void checkForDiscreteCommand(int pin, discreteCommandState_t* state, unsigned long* stateTimestamp);
#endif //LIBHOMEMESH_DISCRETECOMMAND

