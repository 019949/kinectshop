#ifndef STATE_H
#define STATE_H

class state{
public:
    state();
    void            setStateInfo(int info);
    int             getStateInfo();
    void            setId(unsigned int newId);
    int             getId();
private:
    int             stateInfo;
    unsigned int    id;
};

#endif // STATE_H
