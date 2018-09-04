#ifndef LOGOBSERVER_H
#define LOGOBSERVER_H
#include <iostream>
#include <iomanip>
#include <mutex>
#include <fstream>
#include "observer.h"
#include "utils.h"

class LogObserver : public Observer
{
private:
    std::ofstream ost;
public:
    LogObserver(const std::string& file);
    std::mutex mutex;
    ARequestPList failed_requests;
    ARequestPList successful_requests;
    // Observer interface
public:
    void update(unsigned int, std::shared_ptr<Action>) override;
    void getResults() override;
};

#endif // LOGOBSERVER_H
