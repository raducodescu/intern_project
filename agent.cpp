#include "agent.h"

void Agent::notify(std::shared_ptr<Action> action)
{
    foreach (std::shared_ptr<Observer> observer, *m_observers){
        observer->update(GlobalTime::getInstance().getGlobalTime(), action);
    }
}

std::shared_ptr<Track> Agent::getBestTrack(std::shared_ptr<ARequest> req)
{
    std::shared_ptr<Track> track_to_put = nullptr;

    switch (req->getPlaneInfo().getSize()) {
    case PlaneSize::SMALL:
        track_to_put = getBestTypeTrack(req, TrackSize::SMALL);
        if (track_to_put)
            return track_to_put;
    case PlaneSize::MEDIUM:
        track_to_put = getBestTypeTrack(req, TrackSize::MEDIUM);
        if (track_to_put)
            return track_to_put;
    case PlaneSize::LARGE:
        track_to_put = getBestTypeTrack(req, TrackSize::LARGE);
        if (track_to_put)
            return track_to_put;
    }
    return track_to_put;
}

std::shared_ptr<Track> Agent::getBestTypeTrack(std::shared_ptr<ARequest> req, TrackSize size)
{
    std::shared_ptr<Track> track_to_put = nullptr;
    unsigned int requestTime = req->getRequestTime();

    foreach (auto track, *m_tracks) {
        if (track->getSize() == size && track->isRequestAcceptable(req->getPlaneInfo()) && track->getTimeWhenFree() >= requestTime && req->checkFuel(track->getTimeWhenFree())) {
            if (track_to_put == nullptr) {
                track_to_put = track;
            }
            else
            {
                track_to_put = track_to_put->getTimeWhenFree() < track->getTimeWhenFree() ? track_to_put : track;
            }
        }
    }
    return track_to_put;
}


void Agent::processLocalRequests(unsigned int actual_time)
{
    for (auto riteraor = m_agent_requests.begin(); riteraor != m_agent_requests.end();)
    {
        auto request = *riteraor;
        bool processed = false;
        foreach (auto track, *m_tracks)
        {
            if (track->isRequestProcessNow(request))
            {
                if (request->getProcessTime() + request->getPlaneInfo().getTimeOnTrack() == actual_time) {
                    processed = true;
                    track->removeTopRequest();
                    m_agent_requests.erase(riteraor);
                    ActionType type = request->getType() == RequestType::LANDING ? ActionType::LANDING : ActionType::TAKEOFF;
                    std::shared_ptr<Action> action = std::make_shared<Action>(type, request, m_id, track->getId());
                    notify(action);
                }
            }
        }
        if (!processed)
            riteraor++;
    }
}

void Agent::threadMain()
{
    while (m_running || isWorking())
    {
        unsigned int actual_time = GlobalTime::getInstance().getGlobalTime();
        if (actual_time - m_time_last_check == 0)
            continue;

        m_time_last_check = actual_time;
        processLocalRequests(actual_time);

        while (canProcessAnotherRequest() && GlobalTime::getInstance().getGlobalTime() - m_time_last_check < 1)
        {
            std::unique_lock<std::mutex> lock(m_requests_mutex);
            if (m_airport_requests->size() == 0)
            {
                break;
            }
            auto req = m_airport_requests->top();
            if (req->getRequestTime() > actual_time)
            {
                lock.unlock();
                break;
            }
            m_airport_requests->pop();
            std::shared_ptr<Track> trackToPut = getBestTrack(req);
            lock.unlock();
            if (trackToPut == nullptr)
            {
                req->setProcessTime(actual_time);
                std::shared_ptr<Action> action = std::make_shared<Action>(ActionType::FAILED, req, m_id, 0);
                notify(action);
            }
            else
            {
                trackToPut->addRequest(req);
                m_agent_requests.push_back(req);
                std::shared_ptr<Action> action = std::make_shared<Action>(ActionType::RECEIVE, req, m_id, trackToPut->getId());
                notify(action);
            }
        }
    }
}

void Agent::destroyThread()
{
//    while(isWorking())
//    {
//    }

    if (m_thread->joinable())
    {
        m_thread->join();
    }
}

void Agent::stopThread()
{
    m_running = false;
    destroyThread();
}

bool Agent::canProcessAnotherRequest()
{
    return m_agent_requests.size() < m_capacity;
}

bool Agent::isWorking() {
    return m_agent_requests.size() > 0;
}

Agent::Agent(int id, unsigned int capacity, const std::string &name, std::mutex &requests_mutex,
             ARequestPriorityQueue *airport_requests,
             std::vector<std::shared_ptr<Track>> *tracks, ObserverPList *observers) :
            m_id(id), m_capacity(capacity), m_name(name), m_observers(observers), m_tracks(tracks),
            m_airport_requests(airport_requests), m_requests_mutex(requests_mutex)
{
    m_running = false;
    m_time_last_check = 0;
}

unsigned int Agent::getCapacity() const
{
    return m_capacity;
}

void Agent::setCapacity(unsigned int capacity)
{
    this->m_capacity = capacity;
}

const std::string& Agent::getName() const
{
    return m_name;
}

int Agent::getId() const
{
    return m_id;
}

void Agent::startThread()
{
    m_running = true;
    m_thread = std::unique_ptr<std::thread>(new std::thread(&Agent::threadMain, this));
}

QDebug operator<<(QDebug debug, const Agent &agent)
{
    debug << "Agent[" << agent.getId() << "]---Name[" << agent.getName().c_str() << "]---Capacity[" << agent.getCapacity() << "]" << endl;
    return debug;
}

std::ostream& operator<<(std::ostream& ost, const Agent &agent)
{
    ost << "Agent[" << agent.getId() << "]---Name[" << agent.getName() << "]---Capacity[" << agent.getCapacity() << "]" << std::endl;
    return ost;
}
