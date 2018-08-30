#include "planerequest.h"

int PlaneRequest::getId() const
{
    return id;
}

APlane& PlaneRequest::getPlaneInfo() const
{
    return *plane;
}

bool PlaneRequest::isUrgent() const
{
    return urgent;
}

unsigned int PlaneRequest::getRequestTime() const
{
    return requestTime;
}


PlaneRequest::PlaneRequest(unsigned int creationTime, int id, APlane *plane, unsigned int time, bool urgent, RequestType type): ARequest(creationTime, type), id(id), plane(plane), requestTime(time), urgent(urgent)
{

}

PlaneRequest::~PlaneRequest()
{

}
