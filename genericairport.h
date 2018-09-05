#ifndef INTERN_PROJECT_GENERICAIRPORT_H_
#define INTERN_PROJECT_GENERICAIRPORT_H_
#include <string>
#include "requestconsumer.h"

class GenericAirport : public RequestConsumer
{
public:
    GenericAirport();
    virtual ~GenericAirport() = 0;
    virtual void dump_airport(std::ostream&) const = 0;
};

#endif  // INTERN_PROJECT_GENERICAIRPORT_H_
