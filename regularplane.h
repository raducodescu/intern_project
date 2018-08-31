#ifndef INTERN_PROJECT_REGULARPLANE_H_
#define INTERN_PROJECT_REGULARPLANE_H_
#include <iostream>
#include "aplane.h"

class RegularPlane : public APlane
{
 private:
    unsigned int consumption;
    const PlaneType type;
    const PlaneSize size;
    unsigned int timeOnTrack;
 public:
    RegularPlane(unsigned int consumption, PlaneType type, PlaneSize size);
    // APlane interface
    void dump_plane() const override;
    unsigned int getConsumption() const override;
    PlaneType getType() const override;
    PlaneSize getSize() const override;
    unsigned  int getTimeOnTrack() const override;
    void setTimeOnTrack(unsigned int value) override;
};

#endif  // INTERN_PROJECT_REGULARPLANE_H_
