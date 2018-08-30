#ifndef TAKEOFFREQUEST_H
#define TAKEOFFREQUEST_H
#include "planerequest.h"

class TakeOffRequest : public PlaneRequest
{
public:
    TakeOffRequest(unsigned int creation_time, int id, APlane *plane, unsigned int requestTime, bool urgent, RequestType type);

    // PlaneRequest interface
private:
    void dump_request(std::ostream &ost) const override;

    // ARequest interface
public:
    bool checkFuel() const override;
};

#endif // TAKEOFFREQUEST_H
