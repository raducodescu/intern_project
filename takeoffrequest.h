#ifndef INTERN_PROJECT_TAKEOFFREQUEST_H_
#define INTERN_PROJECT_TAKEOFFREQUEST_H_
#include "planerequest.h"

class TakeOffRequest : public PlaneRequest
{
 private:
    void dump_request(std::ostream &ost) const override;

 public:
    TakeOffRequest(unsigned int creation_time, int m_id, APlane *m_plane,
                   unsigned int m_request_time, bool m_urgent, RequestType m_type);
    // ARequest interface   
    bool checkFuel(unsigned int) const override;
};

#endif  // INTERN_PROJECT_TAKEOFFREQUEST_H_
