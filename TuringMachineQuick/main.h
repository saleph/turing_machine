#ifndef MAIN_H
#define MAIN_H
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQmlContext>
#include <iostream>
#include <QStringList>
#include "TMAPI.h"
#include "TMTape.h"
#include "tmtapemodel.h"

class TMMain : QObject {
    Q_OBJECT

    QGuiApplication app;
    QQmlApplicationEngine engine;
    TMAPI api;
    TMTapeModel tapeModel;
    QStringList graphModel;
public:
    TMMain(int argc, char *argv[])
        : app(argc, argv), tapeModel(nullptr, api.tape)
    {
        graphModel << "unod" << "duo";
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
        engine.rootContext()->setContextProperty("tapeModel", &tapeModel);
        engine.rootContext()->setContextProperty("controllerObject", this);
        engine.rootContext()->setContextProperty("graphModel", QVariant::fromValue(graphModel));
        engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
        if (engine.rootObjects().isEmpty())
            exit(-1);


        QObject *root = engine.rootObjects().first();
        QObject::connect(root, SIGNAL(openFileRequest(QVariant)), this, SLOT(handleLoadingFromFile(QVariant)));
        QObject::connect(root, SIGNAL(compileAction()), this, SLOT(handleCompilation()));
        QObject::connect(root, SIGNAL(singleStepAction()), this, SLOT(handleSingleStepping()));
    }
    ~TMMain() { }
    int exec() {
        return app.exec();
    }
signals:
    void commandIdChangeInGraph(int newIndex);

public slots:
    void handleLoadingFromFile(QVariant name) {
        QString filename = name.toUrl().path();
        try {
            auto fn = filename.toStdString();
            api.getDataFromFile(fn);
            updateWholeMainWindow();
            handleGraphCompilation();
            handleTurningBackGraphToStartPosition();
        } catch (const TMException& e) {
            throwExceptionDialogWith(e.what());
            qDebug() << "elo2";
        }
    }

    void handleCompilation() {
        handleGraphCompilation();
    }

    void handleSingleStepping() {
        try {
            api.doSingleStep();
        } catch (const TMException& e) {
            throwExceptionDialogWith(e.what());
        }
//        updateTapeWithOnlyRecentlyDidStep();
        updateRowSelectedInGraphWidget();
    }

private:
    void updateWholeMainWindow() {
        updateGraphTextEdit();
        updateGraphWidget();
    }

    void updateGraphTextEdit() {
        QObject *x = engine.rootObjects().first()->findChild<QObject*>("textEdit");
        QString graph;
        for (auto entry : api.getGraphAsVector()) {
            graph += QString::fromStdString(entry) + "\n";
        }
        x->setProperty("text", graph);
    }

    void updateGraphWidget() {
        graphModel.clear();
        for(auto entry : api.getGraphAsVector()) {
            graphModel.append(QString::fromStdString(entry));
        }
        engine.rootContext()->setContextProperty("graphModel", QVariant::fromValue(graphModel));
    }

    void handleGraphCompilation() {
        try {
            insertAlphabetToApi();
    //        insertGraphFromWidgetToApi();
            insertTextEditGraphToApi();
            updateGraphWidget();
            api.compileInsertedGraph();
            api.turnBackGraphToStartPosition();
//            handleTurningBackGraphToStartPosition();
//            putToStatusBar(tr("Compiled successfully"));
        } catch (const TMException& e) {
            throwExceptionDialogWith(e.what());
        }
    }

    void insertAlphabetToApi() {
//        const std::string alphabet = ui->alphabetLineEdit->text().toStdString();
//        api.insertAlphabet(alphabet);
    }

    void insertTextEditGraphToApi() {
        QObject *textEdit = engine.rootObjects().first()->findChild<QObject*>("textEdit");
        std::istringstream graphAsPlainText(textEdit->property("text").toString().toStdString());
        std::string line;
        std::vector<std::string> graphAsVector;
        while(std::getline(graphAsPlainText, line)) {
            if(line.size() > 0)
                graphAsVector.push_back(line);
        }
        api.insertGraph(std::move(graphAsVector));
    }

    void throwExceptionDialogWith(const std::__cxx11::string &msg) {
        QObject *object = engine.rootObjects().first();
        QMetaObject::invokeMethod(object, "showDialog",
                Q_ARG(QVariant, QVariant(QString::fromStdString(msg))));
    }

    void updateRowSelectedInGraphWidget() {
        emit commandIdChangeInGraph(api.getLocationOfLastCommand());
    }

    void handleTurningBackGraphToStartPosition() {
        try {
            api.turnBackGraphToStartPosition();
        } catch (const TMException& e) {
            throwExceptionDialogWith(e.what());
        }
        updateRowSelectedInGraphWidget();
    }
    void updateTapeWithOnlyRecentlyDidStep() {
//        std::pair<size_t, char> recentChange = api.getPositionAndCharacterRecentlyChangedByStep();
//        setTapeWidgetCharacterAt(recentChange.first, recentChange.second);
//        setCurrentPositionInTapeWidgetAt(api.tape->getHeadPosition());
    }
};

#endif // MAIN_H
