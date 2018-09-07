#include <string>
#include "arequest.h"

RequestType ARequest::getType() const
{
    return m_type;
}

RequestType ARequest::GetTypeFromString(const std::string &str)
{
    if (str.compare("in"))
    {
        return RequestType::LANDING;
    }
    else if (str.compare("out"))
    {
            return RequestType::TAKEOFF;
    }
    throw std::invalid_argument("Direction should be \"in\" for landing or \"out\" for take-off");
}

unsigned int ARequest::getProcessTime() const
{
    return m_processTime;
}

void ARequest::setProcessTime(unsigned int value)
{
    m_processTime = value;
}

ARequest::ARequest(unsigned int creationTime, RequestType type) : m_creationTime(creationTime), m_type(type)
{
}

unsigned int ARequest::getCreationTime() const
{
    return m_creationTime;
}

ARequest::~ARequest()
{
}

std::ostream &operator<<(std::ostream &ost, const ARequest &request)
{
    request.dump_request(ost);
    return ost;
}

bool DereferenceCompareARequest::operator()(const std::shared_ptr<ARequest> req1, const std::shared_ptr<ARequest> req2) const
{
    {
        if (req1->getRequestTime() < req2->getRequestTime())
            return false;
        if (req1->getRequestTime() > req2->getRequestTime())
            return true;

        if (req1->isUrgent() && !req2->isUrgent())
            return false;
        if (!req1->isUrgent() && req2->isUrgent())
            return true;

// Ionut: can these two be const& ?

        const APlane &p1 = req1->getPlaneInfo();
        const APlane &p2 = req2->getPlaneInfo();

        switch (p1.getType())
        {
        case PlaneType::COMMERCIAL:
            if (p2.getType() == PlaneType::MILITARY)
                return true;
            else
            {
                if (p2.getSize() <= p1.getSize())
                    return true;
                else
                    return false;
            }
        case PlaneType::MILITARY:
            if (p2.getType() == PlaneType::COMMERCIAL)
                return false;
            else
            {
                if (p2.getSize() <= p1.getSize())
                    return true;
                else
                    return false;
            }
        }
        return true;
    }
}
