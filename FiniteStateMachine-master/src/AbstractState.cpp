// this is the Abstract state. All other states derivate from this and the code would alwasy return to this state

#include "AbstractState.h"

AbstractState::AbstractState(Machine *context) : _context(context) {}

int AbstractState::getId() const {
    return _id;
}

AbstractState::~AbstractState() {

}



