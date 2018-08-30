#ifndef LOGOBSERVER_H
#define LOGOBSERVER_H
#include "observer.h"

class LogObserver : public Observer
{
public:
    LogObserver(Agent *);

    // Observer interface
public:
    void update() override;
};

#endif // LOGOBSERVER_H
