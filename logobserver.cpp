#include "logobserver.h"

LogObserver::LogObserver()
{
}

void LogObserver::update(unsigned int time, std::shared_ptr<Action> action)
{
    std::unique_lock<std::mutex> lock(mutex);

    std::cout << std::setfill('0') << std::setw(4) << time << ":\t";
    std::cout << action->getType() << " REQUEST---ID:" << action->getRequest()->getId();

    switch (action->getType()) {
    case ActionType::FAILED:
        std::cout << std::endl;
        failed_requests.push_back(action->getRequest());
        break;
    case ActionType::RECEIVE:
        std::cout << "---AgentID: " << action->getAgent_id() << "---TrackID:" << action->getTrack_id() << std::endl;
        break;
    case ActionType::LANDING:
    case ActionType::TAKEOFF:
        std::cout << "---AgentID: " << action->getAgent_id() << "---TrackID:" << action->getTrack_id() << std::endl;
        successful_requests.push_back(action->getRequest());
        break;
    }
    lock.unlock();
}

void LogObserver::getResults()
{
    std::cout << "Get results " << std::endl;
}
