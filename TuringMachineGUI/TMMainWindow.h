#ifndef TMMAINWINDOW_H
#define TMMAINWINDOW_H

#include <QMainWindow>
#include "TMExceptionDialog.h"
#include "TMExceptions.h"
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

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::TMMainWindow *ui;
    TMExceptionDialog *exceptionDialog;
    TMAPI api;

    void setupTapeWidget();
    void updateTape();
    void setTapeWidgetCharacterAt(const size_t pos, const char sign);
    void setCurrentPositionInTapeWidgetAt(const size_t pos);
};

#endif // TMMAINWINDOW_H
