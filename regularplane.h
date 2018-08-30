#ifndef PLANE_H
#define PLANE_H
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
public:
    void dump_plane() const override;
    unsigned int getConsumption() const override;
    PlaneType getType() const override;
    PlaneSize getSize() const override;
    unsigned  int getTimeOnTrack() const override;
    void setTimeOnTrack(unsigned int value) override;
};

#endif // PLANE_H
