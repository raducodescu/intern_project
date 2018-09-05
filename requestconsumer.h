#ifndef INTERN_PROJECT_REQUESTCONSUMER_H_
#define INTERN_PROJECT_REQUESTCONSUMER_H_
#include <memory>
#include "arequest.h"

class RequestConsumer
{
public:
    RequestConsumer();
    virtual void accept(const std::shared_ptr<ARequest> &request) = 0;
    virtual ~RequestConsumer() = 0;
};

#endif  // INTERN_PROJECT_REQUESTCONSUMER_H_
