#ifndef OBSERVER_H
#define OBSERVER_H
#include "agent.h"

class Observer
{
private:
    Agent *agent;
public:
    Observer(Agent *);
    ~Observer();
    Agent *getAgent();

    virtual void update() = 0;

};

#endif // OBSERVER_H
