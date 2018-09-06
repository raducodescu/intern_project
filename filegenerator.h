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

// Ionut: it is a good practice that almost every class has at least one line comment where declared, saying briefly what is about.

class FileGenerator : public RequestGenerator
{
private:
    std::vector<std::shared_ptr<ARequest> > m_requests;
    APlane *createPlaneFromQJsonObject(QJsonObject obj);
public:
    FileGenerator();

    // Ionut: I would prefer to see parameters send by const& where possible.

    void generateRequests(const std::string &filename);
    
    // Ionut: function below needs to be public?

};

#endif  // INTERN_PROJECT_FILEGENERATOR_H_
