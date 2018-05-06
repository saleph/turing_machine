#ifndef TMMAINWINDOW_H
#define TMMAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <string>
#include <iostream>
#include <QTableWidgetItem>
#include <QTimer>
#include <sstream>
#include "TMExceptionDialog.h"
#include "TMExceptions.h"
#include "TMAPI.h"
#include "TMTape.h"
#include "LazyInitializator.h"
#include "tmtapemodel.h"

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

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void setStepTimerInterval(int);

    void proccessSingleStep();

    void on_graphWidget_cellClicked(int row, int column);

    void on_tapeWidget_cellClicked(int row, int column);

    void on_actionCompile_triggered();

    void on_actionBack_to_start_triggered();

    void on_actionExecute_instantly_triggered();

    void on_actionSingle_step_triggered();

    void on_actionAuto_step_triggered();

    void on_action_Load_triggered();

    void on_tapeWidget_itemChanged(QTableWidgetItem *item);

private:
    Ui::TMMainWindow *ui;
    TMExceptionDialog *exceptionDialog;
    TMAPI api;
    QTimer *stepTimer;
    LazyInitializator<std::vector<char>> cachedTape;
    bool autoStepActive = false;
    TMTapeModel tapeModel;

    void setupTapeWidget();
    void updateTape();
    void setTapeWidgetCharacterAt(const size_t pos, const char sign);
    void setCurrentPositionInTapeWidgetAt(const size_t pos);
    void handleGraphCompilation();
    void insertAlphabetToApi();
    void insertGraphFromWidgetToApi();
    void insertTextEditGraphToApi();
    void updateRowSelectedInGraphWidget();
    void updateTextEditWidget();
    void throwExceptionDialogWith(const std::string& msg);
    void putToStatusBar(const QString& msg);
    void updateWholeMainWindow();
    void updateAlphabetWidget();
    void updateGraphWidget();
    void updateTapeWithOnlyRecentlyDidStep();
    void handleTurningBackGraphToStartPosition();
    void handleCompilation();
    void handleExecution();
    void handleLoadingFromFile();
    void handleSingleStepping();
    void handleBackToStart();
    void handleAutoStepping();
    void handleCopyingTape();
    void handlePastingTape();
};

#endif // TMMAINWINDOW_H
