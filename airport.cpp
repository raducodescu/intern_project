#include "airport.h"
#include <memory>
#include <string>
#include <vector>

std::vector<std::shared_ptr<Agent> > Airport::getAgents() const
{
    return agents;
}

std::shared_ptr<ARequest> Airport::getBestRequest()
{
    return nullptr;
}

void Airport::initializeTracks(QJsonValue& tracksValue)
{
    QJsonArray track_list = tracksValue.toArray();

    foreach (const QJsonValue &value, track_list)
    {
        QJsonObject obj = value.toObject();

        if (!obj.value("id").isDouble())
            throw std::invalid_argument("Track id is invalid");
        double d_id = obj.value("id").toDouble();
        if (std::modf(d_id, &d_id) != 0 || d_id < 0)
            throw std::invalid_argument("Track id is invalid");
        int id = static_cast<int>(d_id);

        std::string size = obj.value("size").toString().toStdString();
        std::string type = obj.value("type").toString().toStdString();
        TrackSize tsize = Track::getSizeFromString(size);
        TrackType ttype = Track::getTypeFromString(type);
        tracks.push_back(std::make_shared<Track>(id, tsize, ttype));
    }
}

void Airport::initializeAgents(QJsonValue& controlValue)
{
    QJsonArray control_agents = controlValue.toArray();

    foreach (const QJsonValue &value, control_agents)
    {
        QJsonObject obj = value.toObject();
        if (!obj.contains("name"))
            throw std::invalid_argument("Control agent name is invalid");
        if (!obj.contains("id"))
            throw std::invalid_argument("Control agent id is invalid");
        if (!obj.contains("capacity"))
            throw std::invalid_argument("Control agent capacity is invalid");

        std::string name = obj.value("name").toString().toStdString();
        if (!std::all_of(name.begin(), name.end(), ::isalpha))
            throw std::invalid_argument("Control agent name is invalid");

        if (!obj.value("id").isDouble())
            throw std::invalid_argument("Control agent id is invalid");
        double d_id = obj.value("id").toDouble();
        if (std::modf(d_id, &d_id) != 0 || d_id < 0)
            throw std::invalid_argument("Control agent id is invalid");
        int id = static_cast<int>(d_id);

        if (!obj.value("capacity").isDouble())
            throw std::invalid_argument("Control agent capacity is invalid");
        double d_capacity = obj.value("capacity").toDouble();
        if (std::modf(d_capacity, &d_capacity) != 0 || d_capacity < 0)
            throw std::invalid_argument("Control agent capacity is invalid");
        unsigned int capacity = static_cast<unsigned int>(d_capacity);
        agents.push_back(std::make_shared<Agent>(id, capacity, name, requests_mutex, &requests,
                            &tracks, &observers));
    }
}

void Airport::initializeStaticData(QJsonValue& staticDataValue)
{
    QJsonObject static_data = staticDataValue.toObject();
    int time;
    if (static_data.contains("SMALLTIME"))
    {
        time = static_data.value("SMALLTIME").toInt();
        if (time < 0)
            throw std::invalid_argument("Times on track should be positive");
        airport_planes_times.small_plane_time = static_cast<unsigned>(time);
    }
    if (static_data.contains("MEDIUMTIME"))
    {
        time = static_data.value("MEDIUMTIME").toInt();
        if (time < 0)
            throw std::invalid_argument("Times on track should be positive");
        airport_planes_times.medium_plane_time = static_cast<unsigned>(time);
    }
    if (static_data.contains("LARGETIME"))
    {
        time = static_data.value("LARGETIME").toInt();
        if (time < 0)
            throw std::invalid_argument("Times on track should be positive");
        airport_planes_times.large_plane_time = static_cast<unsigned>(time);
    }
}

Airport::Airport(const std::string &configure_file) : stopped(false)
{
    auto conf_obj = readJson(configure_file);

    QJsonValue agents_value = conf_obj->value("control");
    QJsonValue tracks_value = conf_obj->value("tracks");
    QJsonValue static_data_value = conf_obj->value("static-data");

    if (!agents_value.isArray() || agents_value.toArray().size() == 0)
        throw std::invalid_argument("Control agents needs to be an array of size greater than 1");

    if (!tracks_value.isArray() || tracks_value.toArray().size() == 0)
        throw std::invalid_argument("Tracks needs to be an array of size greater than 1");

    if (!static_data_value.isObject())
        throw std::invalid_argument("Static field needs to be an object");

    observers.push_back(std::shared_ptr<Observer>(new LogObserver));

    initializeTracks(tracks_value);
    initializeAgents(agents_value);
    initializeStaticData(static_data_value);

    foreach (auto a, agents)
    {
        a->startThread();
    }

    std::cout << *this << std::endl;
}

void Airport::accept(const std::shared_ptr<ARequest> &request)
{
    if (stopped)
    {
        std::cout << "Airport is stopped" << std::endl;
    }

    switch (request->getPlaneInfo().getSize())
    {
    case PlaneSize::SMALL:
        request->getPlaneInfo().setTimeOnTrack(airport_planes_times.small_plane_time);
    case PlaneSize::MEDIUM:
        request->getPlaneInfo().setTimeOnTrack(airport_planes_times.medium_plane_time);
    case PlaneSize::LARGE:
        request->getPlaneInfo().setTimeOnTrack(airport_planes_times.large_plane_time);
    }
    bool is_request_good = false;
    foreach(auto track, tracks)
    {
        is_request_good |= track->isRequestAcceptable(request->getPlaneInfo());
    }
    if (!is_request_good)
    {
        std::cout << "Request with id " << request->getId() << " can't be process in this airport" << std::endl;
        return;
    }
    std::unique_lock<std::mutex> lock(requests_mutex);
    requests.push(request);
    lock.unlock();
}

void Airport::stop()
{
    stopped = true;
    bool wait = true;
    while (wait)
    {
        wait = false;
        foreach (auto agent, agents)
            wait |= agent->isWorking();
    }

    foreach (auto agent, agents)
    {
        agent->stopThread();
    }
}

Airport::~Airport()
{
    foreach(auto a, agents)
    {
        a->stopThread();
    }
}

QDebug operator<<(QDebug debug, const Airport &airport) {
    debug << "Airort data:" << endl;
    debug << "Agents:" << endl;
    foreach(auto agent, airport.agents)
    {
        debug << "\t" << *agent << endl;
    }
    debug << endl;
    debug << "Tracks:" << endl;
    foreach(auto track, airport.tracks)
    {
        debug << "\t" << *track << endl;
    }
    return debug;
}

std::ostream &operator<<(std::ostream &ost, const Airport &concreteAirport)
{
    concreteAirport.dump_airport(ost);
    return ost;
}

void Airport::dump_airport(std::ostream &ost) const
{
    ost << "Airort data:" << std::endl;
    ost << "Agents:" << std::endl;
    foreach (auto agent, agents)
    {
        ost << "\t" << *agent;
    }
    ost << std::endl;
    ost << "Tracks: " << std::endl;
    foreach (auto track, tracks)
    {
        ost << "\t" << *track;
    }
}

