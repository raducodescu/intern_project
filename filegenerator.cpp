#include <memory>
#include <string>
#include "filegenerator.h"

FileGenerator::FileGenerator()
{
}

APlane* FileGenerator::createPlaneFromQJsonObject(QJsonObject obj)
{
    APlane *toCreate;
    // Plane fields
    if (!obj.contains("consumption"))
        
  // Ionut: it will be nice in the review meeting you also show how your app handles an invalid input file.
        
        throw std::invalid_argument("Fuel field is consumption");
    if (!obj.contains("type"))
        throw std::invalid_argument("Type field is invalid");
    if (!obj.contains("size"))
        throw std::invalid_argument("Size field is invalid");

    if (!obj.value("consumption").isDouble())
        throw std::invalid_argument("Request consumption is invalid");
    double d_consumption = obj.value("consumption").toDouble();
    if (std::modf(d_consumption, &d_consumption) != 0 || d_consumption < 0)
        throw std::invalid_argument("Request consumption is invalid");
    unsigned int consumption = static_cast<unsigned int>(d_consumption);

    std::string type = obj.value("type").toString().toStdString();
    std::string size = obj.value("size").toString().toStdString();

    toCreate = new RegularPlane(consumption, APlane::GetTypeFromString(type), APlane::GetSizeFromString(size));
    return toCreate;
}

void FileGenerator::generateRequests(std::string filename)
{
    auto file_json = readJson(filename);
    QJsonValue requestsValue = file_json->value("requests");

    if (!requestsValue.isArray())
        throw std::invalid_argument("Requests needs to be an array");

    QJsonArray requestsArray = requestsValue.toArray();
    foreach (const QJsonValue &value, requestsArray)
    {
        QJsonObject obj = value.toObject();
        if (!obj.contains("id"))
            throw std::invalid_argument("Request id is invalid");
        if (!obj.contains("time"))
            throw std::invalid_argument("Request time is invalid");
        if (!obj.contains("urgent"))
            throw std::invalid_argument("Priority field is invalid");
        if (!obj.contains("fuel"))
            throw std::invalid_argument("Fuel field is invalid");
        if (!obj.contains("direction"))
            throw std::invalid_argument("Direction is invalid");


        if (!obj.value("id").isDouble())
            throw std::invalid_argument("Request id is invalid");
        double d_id = obj.value("id").toDouble();
        if (std::modf(d_id, &d_id) != 0 || d_id < 0)
            throw std::invalid_argument("Request id is invalid");
        int id = static_cast<int>(d_id);

        if (!obj.value("time").isDouble())
            throw std::invalid_argument("Request time is invalid");
        double d_time = obj.value("time").toDouble();
        if (std::modf(d_time, &d_time) != 0 || d_time < 0)
            throw std::invalid_argument("Request time is invalid");
        int time = static_cast<int>(d_time);

        if (!obj.value("urgent").isDouble())
            throw std::invalid_argument("Request priority is invalid. It should be 1 or 0");
        double d_urgent = obj.value("urgent").toDouble();
        if (std::modf(d_urgent, &d_urgent) != 0 || d_urgent < 0 || d_urgent > 1)
            throw std::invalid_argument("Request priority is invalid. It should be 1 or 0");
        bool urgent = d_urgent > 0;

        std::string direction = obj.value("type").toString().toStdString();
        RequestType requestType = ARequest::GetTypeFromString(direction);
        std::shared_ptr<ARequest> request;
        
        // Where is this plane object deallocated?
        
        APlane *plane = createPlaneFromQJsonObject(obj);
        unsigned int creationTime = GlobalTime::getInstance().getGlobalTime();
        if (requestType == RequestType::TAKEOFF) {
            request = std::make_unique<TakeOffRequest>(0, id, plane, time, urgent, RequestType::TAKEOFF);
        }
        else
        {
            if (!obj.value("fuel").isDouble())
                throw std::invalid_argument("Request fuel is invalid");
            double d_fuel = obj.value("fuel").toDouble();
            if (std::modf(d_fuel, &d_fuel) != 0 || d_fuel < 0)
                throw std::invalid_argument("Request fuel is invalid");
            int fuel = static_cast<int>(d_fuel);
            request = std::make_shared<LandingRequest>(creationTime, id, plane, time, urgent, fuel, RequestType::LANDING);
        }
        foreach (auto consumer, m_request_consumers)
        {
            consumer->accept(request);
        }
        m_requests.push_back(request);
    }
}
