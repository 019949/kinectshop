#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <QObject>
#include <QDebug>
#include <QMessageBox>

#include "state.h"
#include "transition.h"
#include "sqlfunctions.h"

class automaton : public QObject{
    Q_OBJECT
public:
    explicit automaton(QObject *parent = 0);

signals:
    void      stateChanged(int input);
    void      inputReceived(state from, int input);

public slots:
    void    transitions(int input);
    void       receiveInput(int input); // eine Art setter-Funktion

public:
    void    setState(state newState);
    void    setAmount(unsigned int newAmount);
    void    setPid(unsigned int newPid);

    void    setObj(sqlfunctions* mySqlObj);


    state            getState();
    unsigned int     getAmount();
    unsigned int     getPid();

private:
    state            currentState;
    unsigned int     pid;
    unsigned int     amount;
    sqlfunctions*    connectedObj;
    int              receivedInput;

    // Plan: receivedInput wird erhalten, indem die Funktion receiveInput() ausgelöst wird. receiveInput emittet ein SIGNAL inputReceived(state from, int input)
    // executeTransition(transition myTransition) wird im Konstruktor der Transition mit SIGNAL inputReceived connectet.
};

#endif // AUTOMATON_H
