#include "logobserver.h"

LogObserver::LogObserver()
{

}

void LogObserver::update(unsigned int time, std::shared_ptr<Action> action)
{
    static std::mutex m;
    std::unique_lock<std::mutex> lock(m);
    std::cout << std::setfill('0') << std::setw(4) << time << ":\t";
    std::cout << action->getType() << " REQUEST" << std::endl;
    std::string str;
    switch (action->getType()) {
    case ActionType::FAILED:
        std::cout<< "Request " << action->getRequest()->getId() << " faild.Plane out of fuel and cannot make it by the time one track is free" << std::endl;
        break;
    case ActionType::RECEIVE:
        std::cout << "\t\tAgent[" << action->getAgent_id() << "] receive on track[" << action->getTrack_id() << "] request:" << std::endl;
        std::cout <<  "\t\t"<< *action->getRequest() << std::endl;

        break;
    case ActionType::LANDING:
        std::cout << "\t\tLanding successfull by agent[" << action->getAgent_id() << "] on track:[" << action->getTrack_id() << "] on request:" << std::endl;
        std::cout << "\t\t" <<  *action->getRequest() << std::endl;
        break;
    case ActionType::TAKEOFF:
        std::cout << "\t\tTake-off successfull by agent[" << action->getAgent_id() << "] on track:[" << action->getTrack_id() << "] on request:" << std::endl;
        std::cout << "\t\t" << *action->getRequest() << std::endl;
        break;
    }
    std::cout << str << std::endl;
    lock.unlock();
}
