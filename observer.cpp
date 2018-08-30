#include "observer.h"

Observer::Observer(Agent *agent) : agent(agent)
{

}

Observer::~Observer()
{

}

Agent *Observer::getAgent()
{
    return agent;
}
