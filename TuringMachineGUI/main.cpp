#include "TMMainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TMMainWindow w;
    w.show();

    return a.exec();
}
