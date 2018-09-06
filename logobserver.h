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
    std::ofstream m_ost;
    std::mutex m_mutex;
    ARequestPList m_failed_requests;
    ARequestPList m_successful_requests;
public:
    LogObserver(const std::string& file);

    // Observer interface
    void update(unsigned int, std::shared_ptr<Action>) override;
    void getResults() override;
};

#endif // LOGOBSERVER_H
