#ifndef INTERN_PROJECT_AREQUEST_H_
#define INTERN_PROJECT_AREQUEST_H_
#include "./aplane.h"
#include <memory>
#include <string>
#include <functional>

enum class RequestType
{
    LANDING, TAKEOFF
};

class ARequest
{
private:
    const unsigned int creationTime;
    unsigned int processTime;
    const RequestType type;
public:
    ARequest(unsigned int creationTime, RequestType type);
    virtual ~ARequest();

    static RequestType GetTypeFromString(const std::string&);

    unsigned int getProcessTime() const;
    void setProcessTime(unsigned int value);
    RequestType getType() const;
    unsigned int getCreationTime() const;

    virtual int getId() const = 0;
    virtual APlane& getPlaneInfo() const = 0;
    virtual bool isUrgent() const = 0;
    virtual unsigned int getRequestTime() const = 0;
    virtual bool checkFuel(unsigned int) const = 0;

    virtual void dump_request(std::ostream &ost) const = 0;
    friend std::ostream& operator<<(std::ostream &, const ARequest&);
};


struct DereferenceCompareARequest : public std::binary_function<std::shared_ptr<ARequest>, std::shared_ptr<ARequest>, bool>
{
    bool operator()(const std::shared_ptr<ARequest> req1,
                    const std::shared_ptr<ARequest> req2) const
    {
        if (req1->getRequestTime() < req2->getRequestTime())
            return false;
        if (req1->getRequestTime() > req2->getRequestTime())
            return true;

        if (req1->isUrgent() && !req2->isUrgent())
            return false;
        if (!req1->isUrgent() && req2->isUrgent())
            return true;

        APlane &p1 = req1->getPlaneInfo();
        APlane &p2 = req2->getPlaneInfo();

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
};

#endif  // INTERN_PROJECT_AREQUEST_H_
