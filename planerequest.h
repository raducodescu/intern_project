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
    const int id;
    std::unique_ptr<APlane> plane;
    unsigned int requestTime;
    bool urgent;
 public:
    PlaneRequest(unsigned int creationTime, int id, APlane *plane,
                 unsigned int requestTime, bool urgent, RequestType type);
    ~PlaneRequest() override;
    // ARequest interface
    int getId() const override;
    APlane &getPlaneInfo() const override;
    bool isUrgent() const override;
    unsigned int getRequestTime() const override;
};

#endif  // INTERN_PROJECT_PLANEREQUEST_H_
