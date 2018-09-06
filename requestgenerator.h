#ifndef INTERN_PROJECT_REQUESTGENERATOR_H_
#define INTERN_PROJECT_REQUESTGENERATOR_H_
#include <vector>
#include <qdebug.h>

// Ionut: you could just have a forward declaration for RequestConsumer, instead including its header.

#include "requestconsumer.h"

class RequestGenerator
{
protected:
    std::vector<RequestConsumer*> m_request_consumers;
public:
    RequestGenerator();
    
    // Ionut: can we have pure virtual destructor? Please give the answer during the review meeting.
    
    virtual ~RequestGenerator() = 0;
    void registerConsumer(RequestConsumer *requestConsumer);
    
    // Ionut: I would expect a Generate has also a function like 'generate()' which starts the generation of the items.
};

#endif  // INTERN_PROJECT_REQUESTGENERATOR_H_
