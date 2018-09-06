#ifndef INTERN_PROJECT_APLANE_H_
#define INTERN_PROJECT_APLANE_H_
#include <ostream>
#include <string>

enum class PlaneType
{
    COMMERCIAL,
    MILITARY
};

enum class PlaneSize
{
    SMALL,
    MEDIUM,
    LARGE
};

std::ostream& operator<<(std::ostream &, PlaneSize);
std::ostream& operator<<(std::ostream &, PlaneType);

class APlane
{
public:
    APlane();
    virtual ~APlane();

    static PlaneSize GetSizeFromString(const std::string &);
    static PlaneType GetTypeFromString(const std::string &);

    virtual unsigned int getConsumption() const = 0;
    virtual PlaneType getType() const = 0;
    virtual PlaneSize getSize() const = 0;
    virtual unsigned int getTimeOnTrack() const = 0;
    virtual void setTimeOnTrack(unsigned int) = 0;
    virtual void dump_plane() const = 0;

    friend std::ostream& operator<<(std::ostream &, const APlane&);
};

#endif  // INTERN_PROJECT_APLANE_H_
