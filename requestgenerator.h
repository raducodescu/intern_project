#ifndef REQUESTGENERATOR_H
#define REQUESTGENERATOR_H
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

#endif // REQUESTGENERATOR_H
