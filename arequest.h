#ifndef INTERN_PROJECT_AREQUEST_H_
#define INTERN_PROJECT_AREQUEST_H_
#include "./aplane.h"
#include <memory>
#include <string>
#include <functional>

enum class RequestType
{
    LANDING,
    TAKEOFF
};

class ARequest
{
private:
    const unsigned int m_creationTime;
    unsigned int m_processTime;
    const RequestType m_type;
public:
    ARequest(unsigned int creationTime, RequestType type);
    virtual ~ARequest();

    static RequestType GetTypeFromString(const std::string&);

    unsigned int getProcessTime() const;
    void setProcessTime(unsigned int value);
    RequestType getType() const;
    unsigned int getCreationTime() const;

    virtual int getId() const = 0;
    virtual APlane& getPlaneInfo() const = 0;
    virtual bool isUrgent() const = 0;
    virtual unsigned int getRequestTime() const = 0;
    virtual bool checkFuel(unsigned int) const = 0;

    virtual void dump_request(std::ostream &ost) const = 0;
    friend std::ostream& operator<<(std::ostream &, const ARequest&);
};

/***
 *      Comparator folosit la sortarea requesturilor.
 *      Se sorteaza requesturile descrescator dupa timpul la care doresc sa aterizeze(RequestTime)
 *      Daca acesti timpi sunt egali, se verifica care este mai prioritar, in functie de campul urgent
 *  din cadrul requestului, in cazul in care doua requesturi au aceeasi prioritate se verifica
 *  tipul avionului (COMMERCIAL sau MILITARY). Daca si dupa aceasta au acelasi timp de avion
 *  se ia requestul care are avionul de un size mai mic.
 *
 * ***/

struct DereferenceCompareARequest : public std::binary_function<std::shared_ptr<ARequest>, std::shared_ptr<ARequest>, bool>
{

    bool operator()(const std::shared_ptr<ARequest> req1,
                    const std::shared_ptr<ARequest> req2) const;

};

#endif  // INTERN_PROJECT_AREQUEST_H_
