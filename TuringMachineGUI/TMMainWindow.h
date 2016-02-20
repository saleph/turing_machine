#ifndef TMMAINWINDOW_H
#define TMMAINWINDOW_H

#include <QMainWindow>
#include "TMAPI.h"

namespace Ui {
class TMMainWindow;
}

class TMMainWindow : public QMainWindow
{
    const size_t TAPELENGTH = 1001;

    Q_OBJECT

public:
    explicit TMMainWindow(QWidget *parent = 0);
    ~TMMainWindow();

private:
    Ui::TMMainWindow *ui;
    TMAPI api;

    void setupTapeWidget();
};

#endif // TMMAINWINDOW_H
