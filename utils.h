#ifndef INTERN_PROJECT_UTILS_H_
#define INTERN_PROJECT_UTILS_H_
#include <string>
#include <iostream>
#include <QFile>
#include <QString>
#include <QDebug>
#include <QJsonDocument>
#include <queue>
#include "QJsonObject"
#include <memory>
#include <future>
#include "action.h"
#include "observer.h"

using ARequestPList = std::vector<std::shared_ptr<ARequest>>;
using ObserverPList = std::vector<std::shared_ptr<Observer>>;
using ARequestPriorityQueue = std::priority_queue<std::shared_ptr<ARequest>,
    std::vector<std::shared_ptr<ARequest>>, DereferenceCompareARequest>;


struct AirportPlaneTimes
{
    unsigned int small_plane_time = 1;
    unsigned int medium_plane_time = 2;
    unsigned int large_plane_time = 3;
};

class GlobalTime
{
private:
    volatile unsigned int m_global_time;
    std::future<void> m_future;

    GlobalTime();
    ~GlobalTime();
    GlobalTime(const GlobalTime &) = delete;

    void increment_function();

public:
    unsigned int getGlobalTime() const;
    static GlobalTime& getInstance();
};

std::shared_ptr<QJsonObject> readJson(const std::string &filename);

#endif  // INTERN_PROJECT_UTILS_H_
