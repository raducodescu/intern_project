#include <memory>
#include <string>
#include "utils.h"

std::shared_ptr<QJsonObject> readJson(const std::string &filename)
{
    QString value;
    QFile file;
    QString qfilename = QString::fromStdString(filename);
    file.setFileName(qfilename);
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
    return m_global_time;
}

GlobalTime &GlobalTime::getInstance()
{
    static GlobalTime instance;
    return instance;
}
