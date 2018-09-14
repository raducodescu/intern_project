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
    APlane *createPlaneFromQJsonObject(QJsonObject obj);
public:
    FileGenerator();

    void generateRequests(const std::string &filename);
    

};

#endif  // INTERN_PROJECT_FILEGENERATOR_H_
