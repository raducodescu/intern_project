#ifndef ACTION_H
#define ACTION_H
#include "arequest.h"

enum class ActionType {
    LANDING, TAKEOFF, FAILED, RECEIVE, PROCESS
};

class Action
{
private:
    ActionType type;
public:
    Action(ActionType, ARequest *);
};

#endif // ACTION_H
