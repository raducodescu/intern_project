#include <memory>
#include <string>
#include "utils.h"

std::shared_ptr<QJsonObject> readJson(const std::string &filename)
{
    QString value;
    QFile file;
    QString qfilename = QString::fromStdString(filename);
    file.setFileName(qfilename);
    
    // IONUT: error handling (if file does not exist)
    if (!file.exists())
        throw std::runtime_error("File does not exist");
    
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    value = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(value.toUtf8());
    auto jsonObj = std::make_shared<QJsonObject>(doc.object());
    return jsonObj;
}

GlobalTime::GlobalTime()
{
    m_future = std::async(std::launch::async,
                          &GlobalTime::increment_function, this);
}

GlobalTime::~GlobalTime()
{

}

void GlobalTime::increment_function()
{
    while (true)
    {
        this->m_global_time++;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

unsigned int GlobalTime::getGlobalTime() const
{
    // IONUT: Can there be some synchronization issue between threads trying to read the time and thread that increments the time?
    
    return m_global_time;
}

GlobalTime &GlobalTime::getInstance()
{
    static GlobalTime instance;
    return instance;
}
