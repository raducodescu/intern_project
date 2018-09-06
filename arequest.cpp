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
