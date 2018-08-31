#include "./track.h"
#include <memory>
#include <string>

int Track::getId() const
{
    return id;
}

unsigned int Track::getTimeWhenFree()
{
    if (requests_queue.size() == 0) {
        return GlobalTime::getInstance().getGlobalTime();
    }
    else
    {
        return time_when_free;
    }
}

bool Track::isFree()
{
    return requests_queue.size() == 0;
}

bool Track::isRequestAcceptable(const APlane &plane)
{
    switch (size)
    {
    case TrackSize::LARGE:
        if (plane.getType() == PlaneType::MILITARY)
            return true;
        else if (type == TrackType::ALL)
            return true;
        else
            return false;
    case TrackSize::MEDIUM:
        if (plane.getSize() == PlaneSize::LARGE)
            return false;
        if (plane.getType() == PlaneType::MILITARY)
            return true;
        else if (type == TrackType::ALL)
            return true;
        else
            return false;
    case TrackSize::SMALL:
        if (plane.getSize() != PlaneSize::SMALL)
            return false;
        if (plane.getType() == PlaneType::MILITARY)
            return true;
        else if (type == TrackType::ALL)
            return true;
        else
            return false;
    }
    return false;
}

bool Track::isRequestProcessNow(std::shared_ptr<ARequest> &req) const
{
    if (requests_queue.size() == 0)
        return false;
    return req == requests_queue.front();
}

void Track::removeTopRequest()
{
    requests_queue.pop();
}

void Track::addRequest(std::shared_ptr<ARequest> &request)
{
    auto actual_time = GlobalTime::getInstance().getGlobalTime();
    auto track_time = requests_queue.size() == 0 ? actual_time : time_when_free;
    request->setProcessTime(track_time);
    time_when_free = track_time + request->getPlaneInfo().getTimeOnTrack();
    requests_queue.push(request);
}

Track::Track(int id, TrackSize size, TrackType type) : id(id), size(size), type(type), time_when_free(0)
{
}

TrackType Track::getType() const
{
    return type;
}

TrackType Track::getTypeFromString(const std::string &string)
{
    if (string.compare("all") == 0)

    {
        return TrackType::ALL;
    }
    else if (string.compare("private") == 0)
    {
        return TrackType::PRIVATE;
    }
    throw std::invalid_argument("Type needs to be either all or private");
}

TrackSize Track::getSizeFromString(const std::string &string)
{
    if (string.compare("small") == 0)
    {
        return TrackSize::SMALL;
    }
    else if (string.compare("medium") == 0)
    {
        return TrackSize::MEDIUM;
    }
    else if (string.compare("large") == 0)
    {
        return TrackSize::LARGE;
    }
    throw std::invalid_argument("Size needs to be small, medium or large");
}

QDebug operator<<(QDebug debug, const Track& track)
{
    debug << "Track[" << track.getId() << "]" << " with size "  << endl;
    return debug;
}

TrackSize Track::getSize() const
{
    return size;
}

std::ostream& operator<<(std::ostream& ost, const Track &track)
{
    ost << "Track[" << track.getId() << "]--Size[" << track.getSize() << "]--Type[" << track.getType() << "]" << std::endl;
    return ost;
}

std::ostream &operator<<(std::ostream &ost, TrackType type)
{
    std::string str;
    switch (type)
    {
    case TrackType::ALL:
        str = "ALL";
        break;
    case TrackType::PRIVATE:
        str = "PRIVATE";
        break;
    }
    ost << str;
    return ost;
}

std::ostream &operator<<(std::ostream &ost, TrackSize size)
{
    std::string str;
    switch (size)
    {
    case TrackSize::SMALL:
        str = "SMALL";
        break;
    case TrackSize::MEDIUM:
        str = "MEDIUM";
        break;
    case TrackSize::LARGE:
        str = "LARGE";
        break;
    }
    ost << str;
    return ost;
}
