#ifndef MAIN_H
#define MAIN_H
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQmlContext>
#include <iostream>
#include "TMAPI.h"
#include "TMTape.h"
#include "tmtapemodel.h"

class TMMain : QObject {
    Q_OBJECT

    QGuiApplication app;
    QQmlApplicationEngine engine;
    TMAPI api;
    TMTapeModel tapeModel;
public:
    TMMain(int argc, char *argv[])
        : app(argc, argv), tapeModel(nullptr, api.tape)
    {
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
        engine.rootContext()->setContextProperty("tapeModel", &tapeModel);;
        engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
        if (engine.rootObjects().isEmpty())
            exit(-1);
        QObject *root = engine.rootObjects().first();
        QObject::connect(root, SIGNAL(openFileRequest(QVariant)), this, SLOT(handleLoadingFromFile(QVariant)));
        testFun();
    }
    ~TMMain() { }
    int exec() {
        return app.exec();
    }
public slots:
    void handleLoadingFromFile(QVariant name) {
        QString filename = name.toUrl().path();
//        try {
            auto fn = filename.toStdString();
            api.getDataFromFile(fn);
            updateWholeMainWindow();
//            putToStatusBar(tr("File loaded"));
//            handleGraphCompilation();
//            handleTurningBackGraphToStartPosition();
//        } catch (const TMException& e) {
////            throwExceptionDialogWith(e.what());
//            qDebug() << "elo2";
//        }
    }

private:
    void updateWholeMainWindow() {
        QObject *x = engine.rootObjects().first()->findChild<QObject*>("textEdit");
        QString graph;
        for (auto entry : api.getGraphAsVector()) {
            graph += QString::fromStdString(entry) + "\n";
        }
        x->setProperty("text", graph);

//        for (auto i=0u; i<api.tape->size(); i++) {
//            char f = 'b' + i%('z'-'b');
//            api.tape->at(i) = f;
//        }
//        api.tape->tapeEditNotifier(0, 1001);
//        for (auto x : *(api.tape)) {
//            std::cerr << x;
//        }
    }
    void testFun() {
//        auto x = engine.rootObjects().first()->children();
//        qDebug() << x.size();
//        for (auto o : x) {
//            qDebug() << o->metaObject()->property(0).read(o);
//        }
    }
};

#endif // MAIN_H
