#ifndef INTERN_PROJECT_LANDINGREQUEST_H_
#define INTERN_PROJECT_LANDINGREQUEST_H_
#include "planerequest.h"
#include "utils.h"

class LandingRequest : public PlaneRequest
{
 private:
    unsigned int fuel;
    void dump_request(std::ostream &ost) const override;
 public:
    LandingRequest(unsigned int creation_time, int id, APlane *plane,
                   unsigned int requestTime, bool urgent, unsigned int fuel,
                   RequestType type);
    // PlaneRequest interface
    unsigned int getFuel() const;
    void setFuel(unsigned int value);

    // ARequest interface
    bool checkFuel(unsigned int) const override;
};

#endif  // INTERN_PROJECT_LANDINGREQUEST_H_
