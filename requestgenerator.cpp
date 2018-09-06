#include "requestgenerator.h"

RequestGenerator::RequestGenerator()
{
}

RequestGenerator::~RequestGenerator()
{
}

void RequestGenerator::registerConsumer(RequestConsumer* requestConsumer)
{
   this->m_request_consumers.push_back(requestConsumer);
}
