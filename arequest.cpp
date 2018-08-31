#include "./arequest.h"
#include <string>

RequestType ARequest::getType() const
{
    return type;
}

RequestType ARequest::GetTypeFromString(const std::string &str)
{
    if (str.compare("in"))
    {
        return RequestType::LANDING;
    } else if (str.compare("out"))
    {
            return RequestType::TAKEOFF;
    }
    throw std::invalid_argument("Direction should be \"in\" for landing or \"out\" for take-off");
}

unsigned int ARequest::getProcessTime() const
{
    return processTime;
}

void ARequest::setProcessTime(unsigned int value)
{
    processTime = value;
}

ARequest::ARequest(unsigned int creationTime, RequestType type) : creationTime(creationTime), type(type)
{
}

unsigned int ARequest::getCreationTime() const
{
    return creationTime;
}

ARequest::~ARequest()
{
}

std::ostream &operator<<(std::ostream &ost, const ARequest &request)
{
    request.dump_request(ost);
    return ost;
}
