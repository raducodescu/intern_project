#ifndef ABSTRACTAIRPORT_H
#define ABSTRACTAIRPORT_H
#include <string>
#include "requestconsumer.h"

class GenericAirport : public RequestConsumer
{
public:
    GenericAirport();
    virtual ~GenericAirport() = 0;
    virtual void getResults() = 0;
    virtual void dump_airport(std::ostream&) const = 0;

};

#endif // ABSTRACTAIRPORT_H
