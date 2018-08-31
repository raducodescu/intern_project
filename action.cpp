#include "./action.h"

unsigned int Action::getAgent_id() const
{
    return agent_id;
}

unsigned int Action::getTrack_id() const
{
    return track_id;
}

ActionType Action::getType() const
{
    return type;
}

std::shared_ptr<ARequest> Action::getRequest() const
{
    return request;
}

Action::Action(ActionType type, std::shared_ptr<ARequest> request,
               unsigned int agent_id, unsigned int track_id) : type(type),
    request(request), agent_id(agent_id), track_id(track_id) {}

std::ostream &operator<<(std::ostream &ost, ActionType type)
{
    std::string str;
    switch (type) {
    case ActionType::FAILED:
        str = "FAILED";
        break;
    case ActionType::LANDING:
        str = "SUCCESS";
        break;
    case ActionType::TAKEOFF:
        str = "SUCCESS";
        break;
    case ActionType::RECEIVE:
        str = "RECEIVE";
        break;
    }
    ost << str;
    return ost;
}

