#ifndef INTERN_PROJECT_REGULARPLANE_H_
#define INTERN_PROJECT_REGULARPLANE_H_
#include <iostream>
#include "aplane.h"

class RegularPlane : public APlane
{
private:
    unsigned int m_consumption;
    const PlaneType m_type;
    const PlaneSize m_size;
    unsigned int m_time_on_track;
public:
    RegularPlane(unsigned int m_consumption, PlaneType m_type, PlaneSize m_size);
    // APlane interface
    void dump_plane() const override;
    unsigned int getConsumption() const override;
    PlaneType getType() const override;
    PlaneSize getSize() const override;
    unsigned  int getTimeOnTrack() const override;
    void setTimeOnTrack(unsigned int value) override;
};

#endif  // INTERN_PROJECT_REGULARPLANE_H_
