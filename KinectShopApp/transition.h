#ifndef TRANSITION_H
#define TRANSITION_H

#include "state.h"
#include "automaton.h"

class transition
{
public:
    transition();
    //transition(state initFrom, state initTo, int initInput, automaton *initConnectedAutomaton);

    void        executeTransition();

    state       getFrom();
    void        setFrom(state newState);
    state       getTo();
    void        setTo(state newState);
    int         getInput();
    void        setInput(int newInput);
private:
    state       from;
    state       to;
    int         input;
    //automaton*  connectedAutomaton;
};

#endif // TRANSITION_H
