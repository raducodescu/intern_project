#include "takeoffrequest.h"

TakeOffRequest::TakeOffRequest(unsigned int creationTime, int id, APlane *plane,
                               unsigned int time, bool urgent, RequestType type) :
    PlaneRequest(creationTime, id, plane, time, urgent, type)
{
}

void TakeOffRequest::dump_request(std::ostream &ost) const
{
    ost << "Take-Off by id[" << getId() << "] on time " << getRequestTime() << " with priority " << isUrgent() << std::endl;
}

bool TakeOffRequest::checkFuel(unsigned int time) const
{
    return true;
}
