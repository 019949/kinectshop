#include "transition.h"

transition::transition()
{
}

/*
transition::transition(state initFrom, state initTo, int initInput, automaton* initConnectedAutomaton){
    from = initFrom;
    to = initTo;
    input = initInput;
    connectedAutomaton = initConnectedAutomaton;
    connect(connectedAutomaton, SIGNAL(inputReceived(state, int)), this, SLOT(executeTransition()));
}*/

/*
void transition::executeTransition(){
    this->connectedAutomaton->setState(this->getTo());
    emit connectedAutomaton->stateChanged(this->getInput());
}*/

state transition::getFrom(){
    return from;
}

void transition::setFrom(state newState){
    from = newState;
}

state transition::getTo(){
    return to;
}

void transition::setTo(state newState){
    to = newState;
}

int transition::getInput(){
    return input;
}

void transition::setInput(int newInput){
    input = newInput;
}
