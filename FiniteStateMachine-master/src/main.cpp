// This code is supposed to emulate the turning on and off of light switch
// The state machine has two states (ON (id=1),OFF(id=0)) depending on the status of the switches.
//If the light is OFF, we need to set the switchOn to true and the state will change.
// In the off state, the switchOff signal will not affect the state.
// If the light is ON, we need to set the switchOff to true and the state will change.
// In the on state, the switchOn signal will not affect the state.


#include <iostream>
#include "Machine.h"

enum states{

    OFF,
    ON

};
class AbstractLightState : public AbstractState {

protected:

    bool* _lightSwitchOnPtr;
    bool* _lightSwitchOffPtr;

public:
	// starting point of state machine
    AbstractLightState(Machine *context)  : AbstractState(context) {}

    //Trick to pass next state in the case we use static memory, you will see..
    //AbstractLightState* _NextStateHolder;

	// Creates the ON and OFF light switches
    void attachSwitches(bool* onSig, bool* offsig){

        _lightSwitchOffPtr = offsig;
        _lightSwitchOnPtr = onSig;
    }
};

// Child of Abstracstate
class LightOnState  : public AbstractLightState{

public:

    LightOnState(Machine *context) : AbstractLightState(context) {
        setId();
    }

    void setId() override {

        _id = states ::ON;

    }
    virtual void handle(){


        if(*_lightSwitchOnPtr){

             //Stay in the same state if actual is ON and user pushes On button
            _context->setStatePtr(this);

        }else if (!*_lightSwitchOnPtr) {

             //Stay in the same state if actual is ON and user pushes On button
            _context->setStatePtr(this);

        }

        if(*_lightSwitchOffPtr && _lightSwitchOnPtr){

            //Error  message showing user that they pressed wrong button
            std::cout << "WARNING: both signals ON. This will couse an infinite switching between states in this case."<<std::endl;

        }

        //User changes state by pressing off button
        if (*_lightSwitchOffPtr){

            //Next state is OFF
            _context->setStatePtr(_NextStateHolder);
            std::cout << "OFF" << std::endl;

        }

    }

};

class LightOffState : public AbstractLightState{
public:

    LightOffState(Machine *context) : AbstractLightState(context) {
        setId();
    }

    void setId() override {

        _id = states ::OFF;

    }
    virtual void handle(){

        if(*_lightSwitchOffPtr){

			//If light is OFF allows user to push On button.
            _context->setStatePtr(this);

        }else if (!*_lightSwitchOffPtr) {

            //If light is ON and user pushes On button, no change
            _context->setStatePtr(this);

        }

        if(*_lightSwitchOffPtr && _lightSwitchOnPtr){

            //Error message to show user they pressed wrong button
            std::cout << "WARNING: both signals ON. This will cause an infinite switching between states."<<std::endl;

        }

        //Real state changer
        if (*_lightSwitchOnPtr){

            //Next state is OFF
            _context->setStatePtr(_NextStateHolder);

        }

    }

};

int main() {

    std::cout << "Hello, this is an example for the superFantasticMachine library!" << std::endl;

    //Create a Machine Object

    Machine context;
    Machine* contextPtr = &context;

    //Simulate two switces
    bool switchOn  = false;
    bool switchOff = true;

    //Create a bunch of nodes
    LightOnState  on (contextPtr);
    LightOffState off(contextPtr);

    //Initialize to off
    context.setStatePtr(&off);

    //Initialize states
    on.attachSwitches(&switchOn,&switchOff);
    off.attachSwitches(&switchOn,&switchOff);

    //Set Holders
    on._NextStateHolder  = &off;
    off._NextStateHolder = &on;

    char in;
    bool done = false;
    do {

        std::cout<<std::endl;
        std::cout << "***************************************"<<std::endl;
        std::cout << "ON BUTTON: " << switchOn << "; OFF BUTTON: " << switchOff<<std::endl;
        std::cout << "Press 'a' to switch the OFF button, 's' to switch the ON button or 'c' to continue"<<std::endl;
        std::cout << "Machine STATE is: "<<context.getActualNodeId() << std::endl;
        std::cout << "***************************************"<<std::endl;

        std::cin  >> in;

        switch (in) {

            case 'a':

                switchOff = !switchOff;

                break;

            case 's':

                switchOn = !switchOn;
                break;
            case 'q':
                done = true;
                break;
            case 'c':
                break;

            default :

                std::cout << "Wrong command"<< std::endl;
                done = false;
                break;
        }

        context.handle();
    }while(!done);

    //Return the answer All done with the lights!...
    std::cout << "All done with the lights!"<< std::endl;
    return 0;

}