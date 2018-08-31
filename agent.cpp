#include "agent.h"

void Agent::notify(std::shared_ptr<Action> action)
{
    observer->update(GlobalTime::getInstance().getGlobalTime(), action);
}

std::shared_ptr<Track> Agent::getBestTrack(std::shared_ptr<ARequest> req)
{
    std::shared_ptr<Track> track_to_put = nullptr;
    unsigned int requestTime = req->getRequestTime();
    foreach (auto track, *tracks) {
        if (track->isRequestAcceptable(req->getPlaneInfo()) && track->getTimeWhenFree() >= requestTime && req->checkFuel(track->getTimeWhenFree())) {
            if (track_to_put == nullptr) {
                track_to_put = track;
            } else {
                track_to_put = track_to_put->getTimeWhenFree() < track->getTimeWhenFree() ? track_to_put : track;
            }
        }
    }
    return track_to_put;
}

void Agent::processLocalRequests(unsigned int actual_time)
{
    for (auto riteraor = agent_requests.begin(); riteraor != agent_requests.end();)
    {
        auto request = *riteraor;
        bool processed = false;
        foreach (auto track, *tracks)
        {
            if (track->isRequestProcessNow(request))
            {
                if (request->getProcessTime() + request->getPlaneInfo().getTimeOnTrack() == actual_time) {
                    processed = true;
                    track->removeTopRequest();
                    std::unique_lock<std::mutex> lock(finish_requests_mutex);
                    finish_requests->push_back(request);
                    lock.unlock();
                    agent_requests.erase(riteraor);
                    ActionType type = request->getType() == RequestType::LANDING ? ActionType::LANDING : ActionType::TAKEOFF;
                    std::shared_ptr<Action> action = std::make_shared<Action>(type, request, id, track->getId());
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
    while (running)
    {
        unsigned int actual_time = GlobalTime::getInstance().getGlobalTime();
        if (actual_time - time_last_check == 0)
            continue;

        time_last_check = actual_time;
        processLocalRequests(actual_time);

        while (canProcessAnotherRequest() && GlobalTime::getInstance().getGlobalTime() - time_last_check < 1)
        {
            std::unique_lock<std::mutex> lock(requests_mutex);
            if (airport_requests->size() == 0)
            {
                break;
            }
            auto req = airport_requests->top();
            if (req->getRequestTime() > actual_time)
            {
                lock.unlock();
                break;
            }
            airport_requests->pop();
            std::shared_ptr<Track> trackToPut = getBestTrack(req);
            lock.unlock();
            if (trackToPut == nullptr)
            {
                std::unique_lock<std::mutex> failed_lock(failed_requests_mutex);
                failed_requests->push_back(req);
                failed_lock.unlock();

                std::shared_ptr<Action> action = std::make_shared<Action>(ActionType::FAILED, req, id, 0);
                notify(action);
            }
            else
            {
                trackToPut->addRequest(req);
                agent_requests.push_back(req);
                std::shared_ptr<Action> action = std::make_shared<Action>(ActionType::RECEIVE, req, id, trackToPut->getId());
                notify(action);
            }
        }
    }
}

void Agent::destroyThread()
{
    if (thread->joinable())
    {
        thread->join();
        std::cout << "Thread with id " << thread->get_id() << " has stopped" << std::endl;
    }
}

void Agent::stopThread()
{
    running = false;
    destroyThread();
}

bool Agent::canProcessAnotherRequest()
{
    return agent_requests.size() < capacity;
}

bool Agent::isWorking() {
    return agent_requests.size() > 0;
}

Agent::Agent(int id, unsigned int capacity, const std::string &name, std::mutex &requests_mutex,
             std::priority_queue<std::shared_ptr<ARequest>, std::vector<std::shared_ptr<ARequest>>, DereferenceCompareARequest> *airport_requests,
             std::mutex &finish_requests_mutex, std::vector<std::shared_ptr<ARequest>> *finish_requests,
             std::mutex &failed_requests_mutex, std::vector<std::shared_ptr<ARequest>> *failed_requests,
             std::vector<std::shared_ptr<Track>> *tracks, Observer *observer) :
            id(id), capacity(capacity), name(name), airport_requests(airport_requests), tracks(tracks), finish_requests(finish_requests), failed_requests(failed_requests),
            requests_mutex(requests_mutex), finish_requests_mutex(finish_requests_mutex), failed_requests_mutex(failed_requests_mutex), observer(observer) {
    running = false;
    time_last_check = 0;
}

unsigned int Agent::getCapacity() const
{
    return capacity;
}

void Agent::setCapacity(unsigned int capacity)
{
    this->capacity = capacity;
}

const std::string& Agent::getName() const
{
    return name;
}

int Agent::getId() const
{
    return id;
}

void Agent::startThread()
{
    running = true;
    thread = std::unique_ptr<std::thread>(new std::thread(&Agent::threadMain, this));
}

QDebug operator<<(QDebug debug, const Agent &agent)
{
    debug << "Agent[" << agent.getId() << "]---Name[" << agent.getName().c_str() << "]---Capacity[" << agent.getCapacity() << "]" << endl;
    return debug;
}

std::ostream& operator<<(std::ostream& ost, const Agent &agent)
{
    ost << "Agent[" << agent.getId() << "]--Name[" << agent.getName() << "]--Capacity[" << agent.getCapacity() << "]" << std::endl;
    return ost;
}
