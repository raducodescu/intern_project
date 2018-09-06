#ifndef INTERN_PROJECT_LANDINGREQUEST_H_
#define INTERN_PROJECT_LANDINGREQUEST_H_
#include "planerequest.h"
#include "utils.h"

class LandingRequest : public PlaneRequest
{
private:
    unsigned int m_fuel;
    void dump_request(std::ostream &ost) const override;
public:
    LandingRequest(unsigned int creation_time, int m_id, APlane *m_plane,
                   unsigned int m_request_time, bool m_urgent, unsigned int m_fuel,
                   RequestType m_type);

    unsigned int getFuel() const;
    void setFuel(unsigned int value);

    // ARequest interface
    bool checkFuel(unsigned int) const override;
};

#endif  // INTERN_PROJECT_LANDINGREQUEST_H_
