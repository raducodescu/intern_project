#ifndef OBSERVER_H
#define OBSERVER_H
#include "action.h"

// Ionut: The name of this class is too generic. Name it at least AObserver.

class Observer
{
public:
    Observer();
    virtual ~Observer();
    virtual void update(unsigned int, std::shared_ptr<Action>) = 0;
    virtual void getResults() = 0;
};

#endif // OBSERVER_H
