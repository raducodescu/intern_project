#ifndef OBSERVER_H
#define OBSERVER_H
#include "action.h"


class Observer
{
private:
    Agent *agent;
public:
    Observer(Agent *);
    ~Observer();
    Agent *getAgent();

    virtual void update(Action *) = 0;

};

#endif // OBSERVER_H
