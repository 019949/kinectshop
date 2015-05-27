#include "state.h"

state::state()
{
}

void state::setStateInfo(int info){
    stateInfo = info;
}

int state::getStateInfo(){
    return stateInfo;
}

void state::setId(unsigned int newId){
    id = newId;
}

int state::getId(){
    return id;
}
