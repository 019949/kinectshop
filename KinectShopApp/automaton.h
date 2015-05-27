#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <QObject>
#include <QDebug>
#include <QMessageBox>

#include "state.h"
#include "sqlfunctions.h"

class automaton : public QObject{
    Q_OBJECT
public:
    explicit automaton(QObject *parent = 0);

signals:
    void    stateChanged(int input);

public slots:
    void    transitions(int input);

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
};

#endif // AUTOMATON_H
