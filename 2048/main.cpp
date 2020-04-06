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

/*
    cout << "Hello World!" << endl;

    Plateau P;

    engine.rootContext()->setContextProperty("vueObjPlat", &P);

    cout << P << endl;
    cout << "________" <<endl;

    P.move(1);

    cout << P << endl;
    cout << "________" <<endl;
    P.move(3);

    cout << P << endl;
    cout << "________" <<endl;
*/

    Plateau P;
    engine.rootContext()->setContextProperty("vueObjPlat", &P);
    engine.load(mainQml);

    return app.exec();
}


