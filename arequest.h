#ifndef ABSTRACTREQUEST_H
#define ABSTRACTREQUEST_H
#include <memory>
#include "aplane.h"

enum class RequestType {
    LANDING, TAKEOFF
};

class ARequest : public std::enable_shared_from_this<ARequest>
{
private:
    const unsigned int creationTime;
    unsigned int processTime;
    const RequestType type;
public:
    ARequest(unsigned int creationTime, RequestType type);
    virtual ~ARequest();

    RequestType getType() const;
    unsigned int getCreationTime() const;

    static RequestType GetTypeFromString(const std::string&);
    virtual int getId() const = 0;
    virtual APlane& getPlaneInfo() const = 0;
    virtual bool isUrgent() const = 0;
    virtual unsigned int getRequestTime() const = 0;
    virtual bool checkFuel() const = 0;

    virtual void dump_request(std::ostream &ost) const = 0;
    friend std::ostream& operator<<(std::ostream &, const ARequest&);

    unsigned int getProcessTime() const;
    void setProcessTime(unsigned int value);
};


struct DereferenceCompareARequest : public std::binary_function<std::shared_ptr<ARequest>, std::shared_ptr<ARequest>, bool>
{
    bool operator()(const std::shared_ptr<ARequest> req1, const std::shared_ptr<ARequest> req2) const
    {
        if (req1->getRequestTime() < req2->getRequestTime())
            return false;
        if (req1->getRequestTime() > req2->getRequestTime())
            return true;

        if (req1->isUrgent() && !req2->isUrgent())
            return false;
        if (!req1->isUrgent() && req2->isUrgent())
            return true;

        if (req2->getType() == RequestType::LANDING)
            return true;
        return false;
    }
};

#endif // ABSTRACTREQUEST_H
