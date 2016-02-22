#ifndef TMMAINWINDOW_H
#define TMMAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
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
    void on_compileButton_clicked();

    void on_executeButton_clicked();

    void on_loadButton_clicked();

private:
    Ui::TMMainWindow *ui;
    TMExceptionDialog *exceptionDialog;
    TMAPI api;

    void setupTapeWidget();
    void updateTape();
    void setTapeWidgetCharacterAt(const size_t pos, const char sign);
    void setCurrentPositionInTapeWidgetAt(const size_t pos);
    void insertAlphabetToApi();
    void insertGraphFromWidgetToApi();
    void throwExceptionDialogWith(const std::string& msg);
};

#endif // TMMAINWINDOW_H
