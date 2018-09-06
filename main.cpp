#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <fstream>
#include <iostream>
#include <QDebug>
#include <QTextStream>
#include "airport.h"
#include "filegenerator.h"
#include "dummyconsumer.h"
#include "logobserver.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    GlobalTime::getInstance();

    // Ionut: where are you catching exceptions? I saw your code is throwing some.
    
    std::ofstream ost("airport.log");
    std::shared_ptr<Observer> log_observer(new LogObserver(argv[3]));
    Airport a(argv[1]);
    a.startThreads();
    a.dump_airport(ost);
    a.addObserver(log_observer);
    DummyConsumer dummy;
    FileGenerator fg;
    fg.registerConsumer(&a);

    fg.generateRequests(argv[2]);
    a.stop();
    log_observer->getResults();
    exit(0);
    return 0;
}
