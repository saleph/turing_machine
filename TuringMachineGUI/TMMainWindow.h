#ifndef TMMAINWINDOW_H
#define TMMAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QTimer>
#include "TMExceptionDialog.h"
#include "TMExceptions.h"
#include "TMAPI.h"
#include "TMTape.h"
#include "LazyInitializator.h"

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

    void on_copyTapeButton_clicked();

    void on_pasteTapeButton_clicked();

    void on_graphWidget_cellClicked(int row, int column);

    void on_tapeWidget_cellClicked(int row, int column);

    void on_actionCompile_triggered();

    void on_actionBack_to_start_triggered();

    void on_actionExecute_instantly_triggered();

    void on_actionSingle_step_triggered();

    void on_actionAuto_step_triggered();

    void on_action_Load_triggered();

private:
    Ui::TMMainWindow *ui;
    TMExceptionDialog *exceptionDialog;
    TMAPI api;
    QTimer *stepTimer;
    LazyInitializator<std::vector<char>> cachedTape;
    bool autoStepActive = false;

    void setupTapeWidget();
    void updateTape();
    void setTapeWidgetCharacterAt(const size_t pos, const char sign);
    void setCurrentPositionInTapeWidgetAt(const size_t pos);
    void handleGraphCompilation();
    void insertAlphabetToApi();
    void insertGraphFromWidgetToApi();
    void updateRowSelectedInGraphWidget();
    void throwExceptionDialogWith(const std::string& msg);
    void putToStatusBar(const QString& msg);
    void updateWholeMainWindow();
    void updateAlphabetWidget();
    void updateGraphWidget();
    void updateTapeWithOnlyRecentlyDidStep();
    void handleTurningBackGraphToStartPosition();
};

#endif // TMMAINWINDOW_H
