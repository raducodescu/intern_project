#include "requestgenerator.h"

RequestGenerator::RequestGenerator()
{

}

RequestGenerator::~RequestGenerator()
{

}

void RequestGenerator::registerConsumer(RequestConsumer* requestConsumer)
{
   qDebug() << "Consumer register" << endl;
   this->requestConsumers.push_back(requestConsumer);
}
