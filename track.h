#ifndef INTERN_PROJECT_TRACK_H_
#define INTERN_PROJECT_TRACK_H_
#include <stdexcept>
#include <iostream>
#include <string>
#include <queue>
#include <qdebug.h>
#include <memory>
#include "arequest.h"
#include "utils.h"


enum class TrackType
{
    PUBLIC,
    PRIVATE
};

enum class TrackSize
{
    SMALL,
    MEDIUM,
    LARGE
};

std::ostream& operator<<(std::ostream &, TrackType);
std::ostream& operator<<(std::ostream &, TrackSize);

class Track
{
private:
    const int m_id;
    const TrackSize m_size;
    TrackType m_type;
    std::queue<std::shared_ptr<ARequest> > m_requests_queue;
    unsigned int m_time_when_free;

    friend std::ostream& operator<<(std::ostream& ost, const Track &track);
    friend QDebug operator<<(QDebug, const Track&);
public:
    Track(int m_id, TrackSize m_size, TrackType m_type);
    TrackSize getSize() const;
    TrackType getType() const;
    int getId() const;
    unsigned int getTimeWhenFree() const;
    bool isFree() const;
    bool isRequestAcceptable(const APlane &) const;
    void addRequest(std::shared_ptr<ARequest> &);
    bool isRequestProcessNow(std::shared_ptr<ARequest> &) const;
    void removeTopRequest();

    static TrackType getTypeFromString(const std::string &);
    static TrackSize getSizeFromString(const std::string &);
    
};

#endif  // INTERN_PROJECT_TRACK_H_
