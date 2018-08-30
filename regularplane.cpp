#include "regularplane.h"

unsigned int RegularPlane::getTimeOnTrack() const
{
    return timeOnTrack;
}

void RegularPlane::setTimeOnTrack(unsigned int value)
{
    timeOnTrack = value;
}

RegularPlane::RegularPlane(unsigned int consumption, PlaneType type, PlaneSize size) :
    consumption(consumption), type(type), size(size)
{
    
}


PlaneType RegularPlane::getType() const
{
    return type;
}

PlaneSize RegularPlane::getSize() const
{
    return size;
}

std::ostream& operator<<(std::ostream &ost, const RegularPlane &plane)
{
    plane.dump_plane();
    return ost;
}

void RegularPlane::dump_plane() const
{
    std::cout << "Plane with type " << type << " and size " << size << " with consumption " << consumption << std::endl;
}

unsigned int RegularPlane::getConsumption() const
{
    return consumption;
}
