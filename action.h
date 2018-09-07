#ifndef INTERN_PROJECT_ACTION_H_
#define INTERN_PROJECT_ACTION_H_
#include <memory>
#include "arequest.h"

enum class ActionType
{
    LANDING,
    TAKEOFF,
    FAILED,
    RECEIVE,
    UNSUPPORTED
};

std::ostream& operator<<(std::ostream &, ActionType);

class Action
{
private:
    ActionType m_type;
    std::shared_ptr<ARequest> m_request;
    unsigned int m_agent_id;
    unsigned int m_track_id;
public:
    Action(ActionType m_type, std::shared_ptr<ARequest> m_request,
           unsigned int m_agent_id, unsigned int m_track_id);
    unsigned int getAgent_id() const;
    unsigned int getTrack_id() const;
    ActionType getType() const;
    std::shared_ptr<ARequest> getRequest() const;
};

#endif  // INTERN_PROJECT_ACTION_H_
