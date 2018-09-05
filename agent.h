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
    const int m_id;
    unsigned int m_capacity;
    const std::string m_name;
    unsigned int m_time_last_check;

    std::unique_ptr<std::thread> m_thread;
    std::atomic_bool m_running;
    ObserverPList *m_observers;

    ARequestPList m_agent_requests;
    std::vector<std::shared_ptr<Track>> *m_tracks;
    ARequestPriorityQueue *m_airport_requests;
    std::mutex &m_requests_mutex;

    void threadMain();
    void destroyThread();
    void processLocalRequests(unsigned int actual_time);
    void notify(std::shared_ptr<Action>);
    std::shared_ptr<Track> getBestTrack(std::shared_ptr<ARequest>);
    std::shared_ptr<Track> getBestTypeTrack(std::shared_ptr<ARequest>, TrackSize);
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
