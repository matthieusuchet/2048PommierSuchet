#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
//#include "plateau.h"
#include "tesselle.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    QQmlComponent component(&engine, "tesselle.qml");
    QObject *t = component.create();

 //   qDebug() << "Property value:" << QQmlProperty::read(t, "someNumber").toInt();
  //  QQmlProperty::write(object, "someNumber", 5000);

   // qDebug() << "Property value:" << object->property("someNumber").toInt();
    t->setProperty("parent", case2);

    return app.exec();
}
