#ifndef ACTION_H
#define ACTION_H
#include "arequest.h"
#include "agent.h"

enum class ActionType {
    LANDING, TAKEOFF, FAILED, RECEIVE, PROCESS
};

class Action
{
private:
    ActionType type;
    ARequest *request;
    Agent *agent;
public:
    Action(ActionType, ARequest *, Agent *);
};

#endif // ACTION_H
