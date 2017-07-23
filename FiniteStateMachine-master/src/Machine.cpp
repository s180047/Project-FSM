

#include "Machine.h"

//  call in the main to initiate teh machine
Machine::Machine() {}
Machine::Machine(AbstractState *init) :_state(init){}
Machine::~Machine() {}

void Machine::setStatePtr(AbstractState *state){
    _state = state;
}

AbstractState *Machine::getStatePtr() {
    return _state;
}

void Machine::handle() {

    //Call state handler and set new state
    _state->handle();

}

int Machine::getActualNodeId() {
    return getStatePtr()->getId();
}
