#include "TMMainWindow.h"
#include "ui_TMMainWindow.h"

TMMainWindow::TMMainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::TMMainWindow),
        api(TAPELENGTH) {
    ui->setupUi(this);
    setupTapeWidget();
}

TMMainWindow::~TMMainWindow() {
    delete ui;
}

void TMMainWindow::setupTapeWidget() {
    updateTape();
}

void TMMainWindow::updateTape() {
    for (size_t i = 0; i < TAPELENGTH; i++) {
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

void TMMainWindow::on_pushButton_clicked() {
    api.insertAlphabet(ui->lineEdit->text().toStdString());
    std::vector<std::string> controlGraph;
    controlGraph.reserve(ui->graphWidget->rowCount());
    for (int i = 0; i < ui->graphWidget->rowCount(); i++) {
        controlGraph.push_back(ui->graphWidget->item(i, 0)->text().toStdString());
    }
    api.insertGraph(controlGraph);
    api.compileInsertedGraph();
}

void TMMainWindow::on_pushButton_2_clicked() {
    api.executeGraphInstantly();
    updateTape();
}
