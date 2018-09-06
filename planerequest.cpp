#include "planerequest.h"

int PlaneRequest::getId() const
{
    return m_id;
}

APlane& PlaneRequest::getPlaneInfo() const
{
    return *m_plane;
}

bool PlaneRequest::isUrgent() const
{
    return m_urgent;
}

unsigned int PlaneRequest::getRequestTime() const
{
    return m_request_time;
}


PlaneRequest::PlaneRequest(unsigned int creationTime, int id, APlane *plane,
                           unsigned int time, bool urgent, RequestType type) :
        ARequest(creationTime, type), m_id(id), m_plane(plane),
        m_request_time(time), m_urgent(urgent)
{
}

PlaneRequest::~PlaneRequest()
{
}
