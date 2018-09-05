#include "logobserver.h"

LogObserver::LogObserver(const std::string &file)
{
    m_ost = std::ofstream(file);
}

void LogObserver::update(unsigned int time, std::shared_ptr<Action> action)
{
    std::unique_lock<std::mutex> lock(m_mutex);

    m_ost << std::setfill('0') << std::setw(4) << time << ":\t";
    m_ost << action->getType() << " REQUEST---ID:" << action->getRequest()->getId();

    switch (action->getType()) {
    case ActionType::FAILED:
        m_ost << std::endl;
        m_failed_requests.push_back(action->getRequest());
        break;
    case ActionType::RECEIVE:
        m_ost << "---AgentID: " << action->getAgent_id() << "---TrackID:" << action->getTrack_id() << "---ProcessTime:" << action->getRequest()->getProcessTime() << std::endl;
        break;
    case ActionType::LANDING:
    case ActionType::TAKEOFF:
        m_ost << "---AgentID: " << action->getAgent_id() << "---TrackID:" << action->getTrack_id() << std::endl;
        m_successful_requests.push_back(action->getRequest());
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
    foreach (auto request, m_successful_requests) {
        aux = request->getProcessTime() - request->getRequestTime();
        all_times_sum += aux;
        min_time = aux < min_time ? aux : min_time;
        max_time = aux > max_time ? aux : max_time;
    }
    average = static_cast<double>(all_times_sum / m_successful_requests.size());
    m_ost << "Average waiting time is " << average << std::endl;
    m_ost << "Minimum time in wait queue for a request is " << min_time << " and maximum time is " << max_time << std::endl;
}
