#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <fstream>
#include <iostream>
#include <QDebug>
#include <QTextStream>
#include "airport.h"
#include "filegenerator.h"
#include "dummyconsumer.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    GlobalTime::getInstance();

    std::ofstream ost("airport.log");
    std::shared_ptr<Observer> log_observer(new LogObserver(argv[3]));
    Airport a(argv[1]);

    a.dump_airport(ost);
    a.addObserver(log_observer);
    DummyConsumer dummy;
    FileGenerator fg;
    fg.registerConsumer(&a);

    fg.generateRequests(argv[2]);
    a.stop();
    log_observer->getResults();

    return 0;
}
