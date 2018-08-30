#ifndef REQUESTCONSUMER_H
#define REQUESTCONSUMER_H
#include "arequest.h"
#include <memory>

class RequestConsumer
{
public:
    RequestConsumer();
    virtual void accept(const std::shared_ptr<ARequest> &request) = 0;
    virtual ~RequestConsumer() = 0;
};

#endif // REQUESTCONSUMER_H
