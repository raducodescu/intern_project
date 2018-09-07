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
#include "utils.h"
// Ionut: why do you need to include so many headers here? Please reduce and use fwd declarations where suited instead.

#include "agent.h"
#include "planerequest.h"
#include "track.h"
#include "logobserver.h"

class Airport : public GenericAirport
{
private:
    ARequestPriorityQueue m_requests;
    std::vector<std::shared_ptr<Track> > m_tracks;
    std::vector<std::shared_ptr<Agent> > m_agents;
    std::mutex m_requests_mutex;
    AirportPlaneTimes m_airport_planes_times;
    ObserverPList m_observers;
    std::atomic_bool m_stopped;

    void initializeTracks(const QJsonValue &);
    void initializeAgents(const QJsonValue &);
    void initializeStaticData(const QJsonValue &);
    void notify(std::shared_ptr<Action>);

public:
    explicit Airport(const std::string &configure_file);
    ~Airport() override;

    void startThreads();
    void dump_airport(std::ostream&) const override;
    void accept(const std::shared_ptr<ARequest> &request) override;
    void stop();
    void addObserver(std::shared_ptr<Observer>);
    const std::vector<std::shared_ptr<Agent>>& getAgents() const;


    friend std::ostream& operator<<(std::ostream&, const Airport &);
    friend QDebug operator<<(QDebug, const Airport &);
};

#endif  // INTERN_PROJECT_AIRPORT_H_
