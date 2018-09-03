#include "./aplane.h"
#include <iostream>

APlane::APlane()
{
}

APlane::~APlane()
{
}

std::ostream &operator<<(std::ostream &ost, const APlane &plane)
{
    plane.dump_plane();
    return ost;
}

PlaneSize APlane::GetSizeFromString(const std::string &string)
{
    if (string.compare("small") == 0)
    {
        return PlaneSize::SMALL;
    }
    else if (string.compare("medium") == 0)
    {
        return PlaneSize::MEDIUM;
    }
    else if (string.compare("large") == 0)
    {
        return PlaneSize::LARGE;
    }
    throw std::invalid_argument("Size needs to be small, medium or large");
}

PlaneType APlane::GetTypeFromString(const std::string &string)
{
    if (string.compare("military") == 0)
    {
        return PlaneType::MILITARY;
    } else if (string.compare("commercial") == 0)
    {
        return PlaneType::COMMERCIAL;
    }
    throw std::invalid_argument("Size needs to be small, medium or large");
}

std::ostream &operator<<(std::ostream &ost, PlaneSize size)
{
    std::string str;
    switch (size)
    {
    case PlaneSize::SMALL:
        str = "SMALL";
        break;
    case PlaneSize::MEDIUM:
        str = "MEDIUM";
        break;
    case PlaneSize::LARGE:
        str = "LARGE";
        break;
    }
    ost << str;
    return ost;
}

std::ostream &operator<<(std::ostream &ost, PlaneType type)
{
    std::string str;
    switch (type)
    {
    case PlaneType::COMMERCIAL:
        str = "COMMERCIAL";
        break;
    case PlaneType::MILITARY:
        str = "MILITARY";
        break;
    }
    ost << str;
    return ost;
}

