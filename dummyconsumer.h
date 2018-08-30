#ifndef DUMMYCONSUMER_H
#define DUMMYCONSUMER_H
#include <iostream>
#include "requestconsumer.h"

class DummyConsumer : public RequestConsumer
{
public:
    DummyConsumer();

    // RequestConsumer interface
public:
    void accept(const std::shared_ptr<ARequest> &request) override;
};

#endif // DUMMYCONSUMER_H
