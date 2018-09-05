#ifndef INTERN_PROJECT_PLANEREQUEST_H_
#define INTERN_PROJECT_PLANEREQUEST_H_
#include <memory>
#include <iostream>
#include <vector>
#include "aplane.h"
#include "arequest.h"


class PlaneRequest : public ARequest
{
private:
    const int m_id;
    std::unique_ptr<APlane> m_plane;
    unsigned int m_request_time;
    bool m_urgent;
public:
    PlaneRequest(unsigned int creationTime, int m_id, APlane *m_plane,
                 unsigned int m_request_time, bool m_urgent, RequestType type);
    ~PlaneRequest() override;
    // ARequest interface
    int getId() const override;
    APlane &getPlaneInfo() const override;
    bool isUrgent() const override;
    unsigned int getRequestTime() const override;
};

#endif  // INTERN_PROJECT_PLANEREQUEST_H_
