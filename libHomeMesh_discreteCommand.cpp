#include "libHomeMesh_discreteCommand.h"
#include "Arduino.h"
//pin: The Arduino pin to check
//state: the current state
//stateTimestamp: the time the state was entered
void checkForDiscreteCommand(int pin, discreteCommandState_t* state, unsigned long* stateTimestamp) {
  int command;
	command = digitalRead(pin);
  switch(*state) {
    case DISCRETE_COMMAND_STATE_IDLE:
      if (command == HIGH) {
        *stateTimestamp = millis();
        *state = DISCRETE_COMMAND_STATE_FIRST_HIGH;
      }
      break;
    case DISCRETE_COMMAND_STATE_FIRST_HIGH:
      if (command == LOW) {
        *stateTimestamp = millis();
        *state = DISCRETE_COMMAND_STATE_FIRST_LOW;
      } else if (millis() - *stateTimestamp > STATE_TRANSITION_TIMEOUT) {
        *state = DISCRETE_COMMAND_STATE_IDLE;
      }
      break;
    case DISCRETE_COMMAND_STATE_FIRST_LOW:
      if (command == HIGH) {
          *state = DISCRETE_COMMAND_STATE_ENGAGE;
      }else if (millis() - *stateTimestamp > STATE_TRANSITION_TIMEOUT) {
        *state = DISCRETE_COMMAND_STATE_IDLE;
      }
  }
}


