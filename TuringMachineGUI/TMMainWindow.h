#ifndef TMMAINWINDOW_H
#define TMMAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QTimer>
#include "TMExceptionDialog.h"
#include "TMExceptions.h"
#include "TMAPI.h"

namespace Ui {
class TMMainWindow;
}

class TMMainWindow : public QMainWindow
{
    const size_t TAPE_LENGTH = 1001;

    Q_OBJECT

public:
    explicit TMMainWindow(QWidget *parent = 0);
    ~TMMainWindow();  

private slots:
    void on_compileButton_clicked();

    void on_executeButton_clicked();

    void on_loadButton_clicked();

    void on_singleStepButton_clicked();

    void on_backToStartButton_clicked();

    void on_autoStepButton_clicked();

    void setStepTimerInterval(int);

    void proccessSingleStep();

private:
    Ui::TMMainWindow *ui;
    TMExceptionDialog *exceptionDialog;
    TMAPI api;
    QTimer *stepTimer;

    void setupTapeWidget();
    void updateTape();
    void setTapeWidgetCharacterAt(const size_t pos, const char sign);
    void setCurrentPositionInTapeWidgetAt(const size_t pos);
    void insertAlphabetToApi();
    void insertGraphFromWidgetToApi();
    void updateRowSelectedInGraphWidget();
    void throwExceptionDialogWith(const std::string& msg);
    void putToStatusBar(const QString& msg);
    void updateWholeMainWindow();
    void updateAlphabetWidget();
    void updateGraphWidget();
    void updateTapeWithOnlyRecentlyDidStep();
};

#endif // TMMAINWINDOW_H
