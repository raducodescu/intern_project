#ifndef INTERN_PROJECT_FILEGENERATOR_H_
#define INTERN_PROJECT_FILEGENERATOR_H_
#include <vector>
#include <string>
#include <thread>
#include <chrono>
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
    std::vector<std::shared_ptr<ARequest> > m_requests;
public:
    FileGenerator();

    void generateRequests(std::string filename);
    APlane *createPlaneFromQJsonObject(QJsonObject obj);
};

#endif  // INTERN_PROJECT_FILEGENERATOR_H_
