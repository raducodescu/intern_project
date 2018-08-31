#ifndef INTERN_PROJECT_DUMMYCONSUMER_H_
#define INTERN_PROJECT_DUMMYCONSUMER_H_
#include <memory>
#include <iostream>
#include "requestconsumer.h"


class DummyConsumer : public RequestConsumer
{
 public:
    DummyConsumer();

    // RequestConsumer interface
    void accept(const std::shared_ptr<ARequest> &request) override;
};

#endif  // INTERN_PROJECT_DUMMYCONSUMER_H_
