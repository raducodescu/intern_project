#ifndef FILEGENERATOR_H
#define FILEGENERATOR_H
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <vector>
#include <memory>
#include <QJsonArray>
#include "utils.h"
#include "requestgenerator.h"
#include "regularplane.h"
#include "takeoffrequest.h"
#include "landingrequest.h"
#include "airport.h"

class FileGenerator : public RequestGenerator
{
private:
    std::vector<std::shared_ptr<ARequest> > requests;
public:
    FileGenerator();

    void generateRequests(std::string filename);
    APlane *createPlaneFromQJsonObject(QJsonObject obj);
};

#endif // FILEGENERATOR_H
