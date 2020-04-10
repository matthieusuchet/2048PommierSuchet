#include <iostream>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "plateau.h"
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    const QUrl mainQml(QStringLiteral("qrc:/main.qml"));

    Plateau P;
    engine.rootContext()->setContextProperty("vueObjPlat", &P);
    engine.load(mainQml);

    return app.exec();
}


