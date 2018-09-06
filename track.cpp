#include <memory>
#include <string>
#include "track.h"

int Track::getId() const
{
    return m_id;
}

// Ionut: this function can be const

unsigned int Track::getTimeWhenFree()
{
    if (m_requests_queue.size() == 0) {
        return GlobalTime::getInstance().getGlobalTime();
    }
    else
    {
        return m_time_when_free;
    }
}

// Ionut: this function can be const

bool Track::isFree()
{
    return m_requests_queue.size() == 0;
}

// Ionut: can this function be const?

bool Track::isRequestAcceptable(const APlane &plane)
{
    switch (m_size)
    {
    case TrackSize::LARGE:
        if (plane.getType() == PlaneType::MILITARY)
            return true;
        else if (m_type == TrackType::ALL)
            return true;
        else
            return false;
    case TrackSize::MEDIUM:
        if (plane.getSize() == PlaneSize::LARGE)
            return false;
        if (plane.getType() == PlaneType::MILITARY)
            return true;
        else if (m_type == TrackType::ALL)
            return true;
        else
            return false;
    case TrackSize::SMALL:
        if (plane.getSize() != PlaneSize::SMALL)
            return false;
        if (plane.getType() == PlaneType::MILITARY)
            return true;
        else if (m_type == TrackType::ALL)
            return true;
        else
            return false;
    }
    return false;
}

bool Track::isRequestProcessNow(std::shared_ptr<ARequest> &req) const
{
    if (m_requests_queue.size() == 0)
        return false;
    return req == m_requests_queue.front();
}

void Track::removeTopRequest()
{
    m_requests_queue.pop();
}

void Track::addRequest(std::shared_ptr<ARequest> &request)
{
    auto actual_time = GlobalTime::getInstance().getGlobalTime();
    auto track_time = m_requests_queue.size() == 0 ? actual_time : m_time_when_free;
    request->setProcessTime(track_time);
    m_time_when_free = track_time + request->getPlaneInfo().getTimeOnTrack();
    m_requests_queue.push(request);
}

Track::Track(int id, TrackSize size, TrackType type) : m_id(id), m_size(size), m_type(type), m_time_when_free(0)
{
}

TrackType Track::getType() const
{
    return m_type;
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
    return m_size;
}

std::ostream& operator<<(std::ostream& ost, const Track &track)
{
    ost << "Track[" << track.getId() << "]---Size[" << track.getSize() << "]---Type[" << track.getType() << "]" << std::endl;
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
