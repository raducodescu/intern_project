#ifndef LOGOBSERVER_H
#define LOGOBSERVER_H
#include <iostream>
#include <iomanip>
#include <mutex>
#include "observer.h"

class LogObserver : public Observer
{
public:
    LogObserver();
    // Observer interface
public:
    void update(unsigned int, std::shared_ptr<Action>) override;
};

#endif // LOGOBSERVER_H
