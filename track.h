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
    ALL, PRIVATE
};

enum class TrackSize
{
    SMALL, MEDIUM, LARGE
};

std::ostream& operator<<(std::ostream &, TrackType);
std::ostream& operator<<(std::ostream &, TrackSize);

class Track
{
 private:
    const int id;
    const TrackSize size;
    TrackType type;
    std::queue<std::shared_ptr<ARequest> > requests_queue;
    unsigned int time_when_free;
 public:
    Track(int id, TrackSize size, TrackType type);
    TrackSize getSize() const;
    TrackType getType() const;
    int getId() const;
    unsigned int getTimeWhenFree();
    bool isFree();
    bool isRequestAcceptable(const APlane &);
    void addRequest(std::shared_ptr<ARequest> &);
    bool isRequestProcessNow(std::shared_ptr<ARequest> &) const;
    void removeTopRequest();

    static TrackType getTypeFromString(const std::string &);
    static TrackSize getSizeFromString(const std::string &);
    friend std::ostream& operator<<(std::ostream& ost, const Track &track);
    friend QDebug operator<<(QDebug, const Track&);
};

#endif  // INTERN_PROJECT_TRACK_H_
