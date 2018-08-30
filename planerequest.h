#ifndef REQUEST_H
#define REQUEST_H
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
    PlaneRequest(unsigned int creationTime, int id, APlane *plane, unsigned int requestTime, bool urgent, RequestType type);
    virtual ~PlaneRequest() override;
    // ARequest interface
public:
    int getId() const override;
    APlane &getPlaneInfo() const override;
    bool isUrgent() const override;
    unsigned int getRequestTime() const override;
};

#endif // REQUEST_H
