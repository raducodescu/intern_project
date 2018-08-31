#ifndef INTERN_PROJECT_REQUESTGENERATOR_H_
#define INTERN_PROJECT_REQUESTGENERATOR_H_
#include <vector>
#include <qdebug.h>
#include "requestconsumer.h"

class RequestGenerator
{
 protected:
    std::vector<RequestConsumer*> requestConsumers;
 public:
    RequestGenerator();
    virtual ~RequestGenerator() = 0;
    void registerConsumer(RequestConsumer *requestConsumer);
};

#endif  // INTERN_PROJECT_REQUESTGENERATOR_H_
