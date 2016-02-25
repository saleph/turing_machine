#include "TMMainWindow.h"
#include "ui_TMMainWindow.h"

TMMainWindow::TMMainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::TMMainWindow),
        api(TAPE_LENGTH){
    ui->setupUi(this);
    stepTimer = new QTimer(this);
    connect(stepTimer, SIGNAL(timeout()), this, SLOT(proccessSingleStep()));
    setStepTimerInterval(ui->stepTimeSpinBox->value());
    setupTapeWidget();
}

TMMainWindow::~TMMainWindow() {
    delete ui;
}

void TMMainWindow::setStepTimerInterval(int interval) {
    stepTimer->setInterval(interval);
}

void TMMainWindow::setupTapeWidget() {
    updateTape();
}

void TMMainWindow::updateTape() {
    for (size_t i = 0; i < TAPE_LENGTH; i++) {
        setTapeWidgetCharacterAt(i, api.tape->at(i));
    }
    setCurrentPositionInTapeWidgetAt(api.tape->getHeadPosition());
}

void TMMainWindow::setTapeWidgetCharacterAt(const size_t pos, const char sign) {
    ui->tapeWidget->setItem(0, pos, new QTableWidgetItem(QString(sign)));
}

void TMMainWindow::setCurrentPositionInTapeWidgetAt(const size_t pos) {
    ui->tapeWidget->setCurrentCell(0, pos);
}

void TMMainWindow::on_compileButton_clicked() {
    try {
        insertAlphabetToApi();
        insertGraphFromWidgetToApi();
        api.compileInsertedGraph();
        api.turnBackGraphToStartPosition();
        putToStatusBar(tr("Compiled successfully"));
    } catch (const TMException& e) {
        throwExceptionDialogWith(e.what());
    }
}

void TMMainWindow::insertAlphabetToApi() {
    const std::string alphabet = ui->alphabetLineEdit->text().toStdString();
    api.insertAlphabet(alphabet);
}

void TMMainWindow::insertGraphFromWidgetToApi() {
    const int rowCount = ui->graphWidget->rowCount();
    std::vector<std::string> controlGraph;
    controlGraph.reserve(rowCount);
    for (int i = 0; i < rowCount; i++) {
        QTableWidgetItem *item = ui->graphWidget->item(i, 0);
        if (item)
            controlGraph.push_back(item->text().toStdString());
    }
    api.insertGraph(std::move(controlGraph));
}

void TMMainWindow::throwExceptionDialogWith(const std::__cxx11::string &msg) {
    exceptionDialog = new TMExceptionDialog(this, QString::fromStdString(msg));
    exceptionDialog->setModal(true);
    exceptionDialog->show();
}

void TMMainWindow::putToStatusBar(const QString &msg) {
    ui->statusBar->showMessage(msg, 1500);
}

void TMMainWindow::on_executeButton_clicked() {
    try {
        api.executeGraphInstantly();
        updateTape();
        putToStatusBar(tr("Executed successfully"));
    } catch (const TMException& e) {
        throwExceptionDialogWith(e.what());
    }
    updateRowSelectedInGraphWidget();
}

void TMMainWindow::updateRowSelectedInGraphWidget() {
    int lastCommandPosition = api.getLocationOfLastCommand();
    ui->graphWidget->setCurrentCell(lastCommandPosition, 0);
}

void TMMainWindow::on_loadButton_clicked() {
    QString filename = QFileDialog::getOpenFileName(this, tr("Load file"));
    try {
        api.getDataFromFile(filename.toStdString());
        putToStatusBar(tr("File loaded"));
    } catch (const TMException& e) {
        throwExceptionDialogWith(e.what());
    }
    updateWholeMainWindow();
}

void TMMainWindow::updateWholeMainWindow() {
    updateTape();
    updateAlphabetWidget();
    updateGraphWidget();
}

void TMMainWindow::updateAlphabetWidget() {
    ui->alphabetLineEdit->setText(QString::fromStdString(api.getAlphabet()));
}

void TMMainWindow::updateGraphWidget() {
    ui->graphWidget->setRowCount(0);
    const std::vector<std::string> graphAsText = api.getGraphAsVector();
    for (size_t i = 0; i < graphAsText.size(); i++) {
        ui->graphWidget->insertRow(i);
        ui->graphWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(graphAsText[i])));
    }
    ui->graphWidget->updateRowsLabels();
}

void TMMainWindow::on_singleStepButton_clicked() {
    try {
        api.doSingleStep();
    } catch (const TMException& e) {
        throwExceptionDialogWith(e.what());
    }
    updateTapeWithOnlyRecentlyDidStep();
    updateRowSelectedInGraphWidget();
}

void TMMainWindow::updateTapeWithOnlyRecentlyDidStep() {
    std::pair<size_t, char> recentChange = api.getPositionAndCharacterRecentlyChangedByStep();
    setTapeWidgetCharacterAt(recentChange.first, recentChange.second);
    setCurrentPositionInTapeWidgetAt(api.tape->getHeadPosition());
}

void TMMainWindow::on_backToStartButton_clicked() {
    api.turnBackGraphToStartPosition();
    updateRowSelectedInGraphWidget();
}

void TMMainWindow::on_autoStepButton_clicked() {
    if (ui->autoStepButton->isChecked()) {
        stepTimer->start();
    } else {
        stepTimer->stop();
    }
}

void TMMainWindow::proccessSingleStep() {
    try {
        api.doSingleStep();
        updateTapeWithOnlyRecentlyDidStep();
        updateRowSelectedInGraphWidget();
    } catch (const TMException& e) {
        ui->autoStepButton->setChecked(false);
        stepTimer->stop();
        updateTapeWithOnlyRecentlyDidStep();
        updateRowSelectedInGraphWidget();
        throwExceptionDialogWith(e.what());
    }
}

void TMMainWindow::on_copyTapeButton_clicked() {
    ui->pasteTapeButton->setProperty("enabled", true);
    cachedTape = { api.tape->begin(), api.tape->end() };
}

void TMMainWindow::on_pasteTapeButton_clicked() {
    for (size_t i = 0; i < TAPE_LENGTH; i++) {
        setTapeWidgetCharacterAt(i, cachedTape->at(i));
    }
}
