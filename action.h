#ifndef INTERN_PROJECT_ACTION_H_
#define INTERN_PROJECT_ACTION_H_
#include <memory>
#include "arequest.h"

enum class ActionType
{
    LANDING, TAKEOFF, FAILED, RECEIVE
};

std::ostream& operator<<(std::ostream &, ActionType);

class Action
{
 private:
    ActionType type;
    std::shared_ptr<ARequest> request;
    unsigned int agent_id;
    unsigned int track_id;
 public:
    Action(ActionType type, std::shared_ptr<ARequest> request,
           unsigned int agent_id, unsigned int track_id);
    unsigned int getAgent_id() const;
    unsigned int getTrack_id() const;
    ActionType getType() const;
    std::shared_ptr<ARequest> getRequest() const;
};

#endif  // INTERN_PROJECT_ACTION_H_
