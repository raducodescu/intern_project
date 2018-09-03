#ifndef INTERN_PROJECT_AGENT_H_
#define INTERN_PROJECT_AGENT_H_
#include <string>
#include <iostream>
#include <thread>
#include <chrono>
#include <memory>
#include <mutex>
#include <qdebug.h>
#include <queue>
#include <vector>
#include "arequest.h"
#include "track.h"
#include "utils.h"
#include "action.h"
#include "observer.h"

class Agent
{
 private:
    const int id;
    unsigned int capacity;
    const std::string name;
    unsigned int time_last_check;
    ARequestPriorityQueue *airport_requests;
    std::vector<std::shared_ptr<Track>> *tracks;
    ARequestPList agent_requests;
    std::unique_ptr<std::thread> thread;
    std::atomic_bool running;
    std::mutex &requests_mutex;
    ObserverPList *observers;

    void threadMain();
    void destroyThread();
    void processLocalRequests(unsigned int actual_time);
    void notify(std::shared_ptr<Action>);
    std::shared_ptr<Track> getBestTrack(std::shared_ptr<ARequest>);
 public:
    Agent(int, unsigned int, const std::string &, std::mutex &, ARequestPriorityQueue *,
          std::vector<std::shared_ptr<Track> > *, ObserverPList *);
    unsigned int getCapacity() const;
    void setCapacity(unsigned int value);
    const std::string& getName() const;
    int getId() const;
    void startThread();
    void stopThread();
    bool canProcessAnotherRequest();
    bool isWorking();

    friend std::ostream& operator<<(std::ostream& ost, const Agent &agent);
    friend QDebug operator<<(QDebug, const Agent &agent);
};

#endif  // INTERN_PROJECT_AGENT_H_
