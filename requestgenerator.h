#ifndef INTERN_PROJECT_REQUESTGENERATOR_H_
#define INTERN_PROJECT_REQUESTGENERATOR_H_
#include <vector>
#include <qdebug.h>

class RequestConsumer;


class RequestGenerator
{
protected:
    std::vector<RequestConsumer*> m_request_consumers;
public:
    RequestGenerator();
    
    virtual ~RequestGenerator() = 0;
    void registerConsumer(RequestConsumer *requestConsumer);

};

#endif  // INTERN_PROJECT_REQUESTGENERATOR_H_
