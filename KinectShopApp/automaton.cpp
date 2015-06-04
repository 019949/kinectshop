#include "automaton.h"

automaton::automaton(QObject *parent) :
    QObject(parent)
{
    //connect(this,SIGNAL(stateChanged(int)),this,SLOT(transitions(int)));

    state idle;
    idle.setId(0);
    idle.setStateInfo(0);
    currentState = idle;

    // Zu Testzwecken
    pid = 2;

    // Testfunktion
    // qDebug() << currentState.getId();
}

// ///////////////////// Transitions /////////////////////

// Zustände
#define IDLE 0
#define SELECTED 1
#define AMOUNTSET 2
#define FINISHED 3

state idle, selected, amountset, finished;

// Eingaben
// Mengen
#define ONE 1
#define TWO 2
//  andere Befehle
#define SELECT 100
#define PUTINCART 101
#define BACK 102
#define CANCEL 103
#define MORE 104

void automaton::transitions(int input){

    idle.setId(IDLE);
    selected.setId(SELECTED);
    amountset.setId(AMOUNTSET);
    finished.setId(FINISHED);

    QMessageBox msgBox;
    msgBox.setText("Die StateId ist: "+QString::number(currentState.getId())+"\nDer Input ist: "+QString::number(input));
    msgBox.exec();

    switch (currentState.getId()){

    case IDLE:
        switch (input) {
        case SELECT:
            // neue pid hier setzen
            setState(selected);
            break;
        default:
            qDebug() << "FEHLER: case IDLE";
            break;
        }
    break;

    case SELECTED:
        switch (input) {
        case ONE:
            setState(amountset);
            setAmount(1);
            break;
        case TWO:
            setState(amountset);
            setAmount(2);
            break;
        case BACK:
            setState(idle);
            break;
        case CANCEL:
            setState(idle);
            break;
        default:
            qDebug() << "FEHLER: case SELECTED";
            break;
        }
    break;

    case AMOUNTSET:
        switch (input) {
        case PUTINCART:
        {
            setState(finished);
            QSqlQuery query;
            query.prepare("SELECT price, title FROM products WHERE id = :pid");
            query.bindValue(":pid", pid);
            query.exec();
            query.next();
            double price = query.value(0).toDouble();
            QString title = query.value(1).toString();
            connectedObj->addToCart(pid,amount,price,title);
            break;
        }
        case BACK:
            setState(selected);
            setAmount(0);
            break;
        case CANCEL:
            setState(idle);
            setAmount(0);
            break;
        default:
            qDebug() << "FEHLER: case AMOUNTSET";
            break;
        }
    break;

    case FINISHED:
        switch (input) {
        case MORE:
            setState(idle);
            setAmount(0);
            break;
        default:
            qDebug() << "FEHLER: case FINISHED";
            break;
        }
    break;

    default:
        qDebug() << "FEHLER: switch";
        break;
    }
}


void automaton::receiveInput(int input){
    receivedInput = input;
    emit inputReceived(currentState, input);
}

// ///////////////////////////////////////////////////////

void automaton::setState(state newState){
    currentState = newState;

    // Testfunktion
    QMessageBox msgBox;
    msgBox.setText("Die Id des States auf den zu setzen ist, ist: "+ QString::number(newState.getId()));
    msgBox.exec();

    msgBox.setText("Die Id des neuen States ist: "+ QString::number(currentState.getId()));
    msgBox.exec();
}

void automaton::setAmount(unsigned int newAmount){
    amount = newAmount;
}

void automaton::setPid(unsigned int newPid){
    pid = newPid;
}

void automaton::setObj(sqlfunctions *obj){
    connectedObj = obj;
}

state automaton::getState(){
    return currentState;
}

unsigned int automaton::getAmount(){
    return amount;
}

unsigned int automaton::getPid(){
    return pid;
}
