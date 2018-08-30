#ifndef UTILS_H
#define UTILS_H
#include "string"
#include <iostream>
#include <QFile>
#include <QString>
#include <QDebug>
#include <QJsonDocument>
#include "QJsonObject"
#include <memory>
#include <future>

struct AirportPlaneTimes
{
    unsigned int small_plane_time = 1;
    unsigned int medium_plane_time = 2;
    unsigned int large_plane_time = 3;
};

class GlobalTime
{
private:
    unsigned int global_time;
    std::future<void> future;
    GlobalTime();
    void increment_function();
public:
    unsigned int getGlobalTime() const;
    static GlobalTime& getInstance();
};


std::shared_ptr<QJsonObject> readJson(const std::string &filename);

#endif // UTILS_H
