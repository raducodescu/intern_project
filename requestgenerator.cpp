#include "./requestgenerator.h"

RequestGenerator::RequestGenerator()
{
}

RequestGenerator::~RequestGenerator()
{
}

void RequestGenerator::registerConsumer(RequestConsumer* requestConsumer)
{
   this->requestConsumers.push_back(requestConsumer);
}
