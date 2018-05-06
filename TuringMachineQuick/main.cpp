#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQmlContext>
#include "TMAPI.h"
#include "TMTape.h"
#include "tmtapemodel.h"
#include "main.h"

int main(int argc, char *argv[])
{
    TMMain main(argc, argv);
    return main.exec();
}
