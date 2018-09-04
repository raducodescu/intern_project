#include "logobserver.h"

LogObserver::LogObserver(const std::string &file)
{
    ost = std::ofstream(file);
}

void LogObserver::update(unsigned int time, std::shared_ptr<Action> action)
{
    std::unique_lock<std::mutex> lock(mutex);

    ost << std::setfill('0') << std::setw(4) << time << ":\t";
    ost << action->getType() << " REQUEST---ID:" << action->getRequest()->getId();

    switch (action->getType()) {
    case ActionType::FAILED:
        ost << std::endl;
        failed_requests.push_back(action->getRequest());
        break;
    case ActionType::RECEIVE:
        ost << "---AgentID: " << action->getAgent_id() << "---TrackID:" << action->getTrack_id() << "---ProcessTime:" << action->getRequest()->getProcessTime() << std::endl;
        break;
    case ActionType::LANDING:
    case ActionType::TAKEOFF:
        ost << "---AgentID: " << action->getAgent_id() << "---TrackID:" << action->getTrack_id() << std::endl;
        successful_requests.push_back(action->getRequest());
        break;
    }
    lock.unlock();
}

void LogObserver::getResults()
{
    uint min_time = UINT_MAX;
    uint max_time = 0;
    double average;
    uint all_times_sum = 0;
    uint aux;
    foreach (auto request, successful_requests) {
        aux = request->getProcessTime() - request->getRequestTime();
        all_times_sum += aux;
        min_time = aux < min_time ? aux : min_time;
        max_time = aux > max_time ? aux : max_time;
    }
    average = static_cast<double>(all_times_sum / successful_requests.size());
    ost << "Averate waiting time is " << average << std::endl;
    ost << "Minimum time in wait queue for a request is " << min_time << " and maximum time is " << max_time << std::endl;
}
