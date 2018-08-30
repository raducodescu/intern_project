#ifndef LANDINGREQUEST_H
#define LANDINGREQUEST_H
#include "planerequest.h"
#include "utils.h"

class LandingRequest : public PlaneRequest
{
private:
    unsigned int fuel;
public:
    LandingRequest(unsigned int creation_time, int id, APlane *plane, unsigned int requestTime, bool urgent, unsigned int fuel, RequestType type);
    // PlaneRequest interface
    unsigned int getFuel() const;
    void setFuel(unsigned int value);

private:
    void dump_request(std::ostream &ost) const override;

    // ARequest interface
public:
    bool checkFuel() const override;
};

#endif // LANDINGREQUEST_H
