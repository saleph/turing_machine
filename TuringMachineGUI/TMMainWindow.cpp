#include "TMMainWindow.h"
#include "ui_TMMainWindow.h"

TMMainWindow::TMMainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::TMMainWindow),
        api(TAPE_LENGTH),
        tapeModel(nullptr, api.tape)
{
    ui->setupUi(this);
    ui->tapeWidget->horizontalHeader()->hide();
    stepTimer = new QTimer(this);
    connect(stepTimer, SIGNAL(timeout()), this, SLOT(proccessSingleStep()));
    setStepTimerInterval(ui->stepTimeSpinBox->value());
    setupTapeWidget();
}

TMMainWindow::~TMMainWindow() {
    delete ui;
}

void TMMainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    setCurrentPositionInTapeWidgetAt(api.tape->getHeadPosition());
}

void TMMainWindow::setStepTimerInterval(int interval) {
    stepTimer->setInterval(interval);
}

void TMMainWindow::setupTapeWidget() {
    //updateTape();
    ui->tapeWidget->setModel(&tapeModel);
}

void TMMainWindow::updateTape() {
    for (size_t i = 0; i < TAPE_LENGTH; i++) {
        setTapeWidgetCharacterAt(i, api.tape->at(i));
    }
    setCurrentPositionInTapeWidgetAt(api.tape->getHeadPosition());
}

void TMMainWindow::setTapeWidgetCharacterAt(const size_t pos, const char sign) {
    //ui->tapeWidget->setItem(0, pos, new QTableWidgetItem(QString(sign)));
}

void TMMainWindow::setCurrentPositionInTapeWidgetAt(const size_t pos) {
    //ui->tapeWidget->setCurrentCell(0, pos);
}

void TMMainWindow::handleCompilation() {
    handleGraphCompilation();
}

void TMMainWindow::handleGraphCompilation() {
    try {
        insertAlphabetToApi();
//        insertGraphFromWidgetToApi();
        insertTextEditGraphToApi();
        updateGraphWidget();
        api.compileInsertedGraph();
        api.turnBackGraphToStartPosition();
        handleTurningBackGraphToStartPosition();
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

void TMMainWindow::insertTextEditGraphToApi() {
    std::istringstream graphAsPlainText(ui->graphTextEdit->toPlainText().toStdString());
    std::string line;
    std::vector<std::string> graphAsVector;
    while(std::getline(graphAsPlainText, line)) {
        if(line.size() > 0)
            graphAsVector.push_back(line);
    }
    api.insertGraph(std::move(graphAsVector));
}

void TMMainWindow::throwExceptionDialogWith(const std::__cxx11::string &msg) {
    exceptionDialog = new TMExceptionDialog(this, QString::fromStdString(msg));
    exceptionDialog->setModal(true);
    exceptionDialog->show();
}

void TMMainWindow::putToStatusBar(const QString &msg) {
    ui->statusBar->showMessage(msg, 1500);
}

void TMMainWindow::handleExecution() {
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

void TMMainWindow::handleLoadingFromFile() {
    QString filename = QFileDialog::getOpenFileName(this, tr("Load file"));
    try {
        api.getDataFromFile(filename.toStdString());
        updateWholeMainWindow();
        putToStatusBar(tr("File loaded"));
        handleGraphCompilation();
        handleTurningBackGraphToStartPosition();
    } catch (const TMException& e) {
        throwExceptionDialogWith(e.what());
    }
}

void TMMainWindow::updateWholeMainWindow() {
    updateTape();
    updateAlphabetWidget();
    updateGraphWidget();
    updateTextEditWidget();
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

void TMMainWindow::updateTextEditWidget() {
    const std::vector<std::string> graphAsTextLines = api.getGraphAsVector();
    QString graphAsText;
    for (auto &&line : graphAsTextLines) {
        graphAsText.append(QString::fromStdString(line));
        graphAsText.append("\n");
    }
    ui->graphTextEdit->setText(graphAsText);
}

void TMMainWindow::handleSingleStepping() {
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

void TMMainWindow::handleBackToStart() {
    handleTurningBackGraphToStartPosition();
}

void TMMainWindow::handleTurningBackGraphToStartPosition() {
    try {
        api.turnBackGraphToStartPosition();
    } catch (const TMException& e) {
        throwExceptionDialogWith(e.what());
    }
    updateRowSelectedInGraphWidget();
}

void TMMainWindow::handleAutoStepping() {
    autoStepActive = !autoStepActive;
    if (autoStepActive) {
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
        autoStepActive = false;
        stepTimer->stop();
        updateTapeWithOnlyRecentlyDidStep();
        updateRowSelectedInGraphWidget();
        throwExceptionDialogWith(e.what());
    }
}

void TMMainWindow::handleCopyingTape() {
    cachedTape = std::vector<char>(api.tape->begin(), api.tape->end());
}

void TMMainWindow::handlePastingTape() {
    *api.tape = *cachedTape;
    updateTape();
}

void TMMainWindow::on_graphWidget_cellClicked(int row, int) {
    api.makeCurrentCmdACommandWithLocation(row);
}

void TMMainWindow::on_tapeWidget_cellClicked(int, int column) {
    api.setHeadPosition(column);
}

void TMMainWindow::on_actionCompile_triggered()
{
    handleCompilation();
}

void TMMainWindow::on_actionBack_to_start_triggered()
{
    handleBackToStart();
}

void TMMainWindow::on_actionExecute_instantly_triggered()
{
    handleExecution();
}

void TMMainWindow::on_actionSingle_step_triggered()
{
    handleSingleStepping();
}

void TMMainWindow::on_actionAuto_step_triggered()
{
    handleAutoStepping();
}

void TMMainWindow::on_action_Load_triggered()
{
    handleLoadingFromFile();
}

void TMMainWindow::on_tapeWidget_itemChanged(QTableWidgetItem *item)
{
    api.tape->operator [](item->column()) = item->text().at(0).toLatin1();
}
