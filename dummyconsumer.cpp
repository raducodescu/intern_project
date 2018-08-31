#include "./dummyconsumer.h"
#include <memory>

DummyConsumer::DummyConsumer()
{
}

void DummyConsumer::accept(const std::shared_ptr<ARequest> &request)
{
    std::cout << "Dummy consumer receive:  " << *request << std::endl;
}
