#include "./regularplane.h"

unsigned int RegularPlane::getTimeOnTrack() const
{
    return m_time_on_track;
}

void RegularPlane::setTimeOnTrack(unsigned int value)
{
    m_time_on_track = value;
}

RegularPlane::RegularPlane(unsigned int consumption, PlaneType type, PlaneSize size) :
    m_consumption(consumption), m_type(type), m_size(size)
{
}


PlaneType RegularPlane::getType() const
{
    return m_type;
}

PlaneSize RegularPlane::getSize() const
{
    return m_size;
}

std::ostream& operator<<(std::ostream &ost, const RegularPlane &plane)
{
    plane.dump_plane();
    return ost;
}

void RegularPlane::dump_plane() const
{
    std::cout << "Plane with type " << m_type << " and size " << m_size << " with consumption " << m_consumption << std::endl;
}

unsigned int RegularPlane::getConsumption() const
{
    return m_consumption;
}
