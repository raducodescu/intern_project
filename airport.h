#ifndef INTERN_PROJECT_AIRPORT_H_
#define INTERN_PROJECT_AIRPORT_H_
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <queue>
#include <cmath>
#include <limits>
#include <future>
#include <memory>
#include <string>
#include <vector>
#include "genericairport.h"
#include "agent.h"
#include "planerequest.h"
#include "track.h"
#include "utils.h"
#include "logobserver.h"

class Airport : public GenericAirport
{
 private:
    std::priority_queue<std::shared_ptr<ARequest>,
            std::vector<std::shared_ptr<ARequest>>,
            DereferenceCompareARequest> requests;
    std::vector<std::shared_ptr<ARequest>> finish_requests;
    std::vector<std::shared_ptr<ARequest>> failed_requests;
    std::vector<std::shared_ptr<Track> > tracks;
    std::vector<std::shared_ptr<Agent> > agents;
    std::mutex requests_mutex;
    std::mutex finish_requests_mutex;
    std::mutex failed_requests_mutex;
    AirportPlaneTimes airport_planes_times;
    Observer *observer;

    std::shared_ptr<ARequest> getBestRequest();
    void initializeTracks(QJsonValue &);
    void initializeAgents(QJsonValue &);
    void initializeStaticData(QJsonValue &);
    // AbstractAirport interface

 public:
    void dump_airport(std::ostream&) const override;
    void getResults() override;
    void accept(const std::shared_ptr<ARequest> &request) override;

    explicit Airport(const std::string &configure_file);
    ~Airport() override;
    friend std::ostream& operator<<(std::ostream&, const Airport &);
    friend QDebug operator<<(QDebug, const Airport &);
    std::vector<std::shared_ptr<Agent> > getAgents() const;
};

#endif  // INTERN_PROJECT_AIRPORT_H_
