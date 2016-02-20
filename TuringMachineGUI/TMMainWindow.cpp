#include "TMMainWindow.h"
#include "ui_TMMainWindow.h"

TMMainWindow::TMMainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::TMMainWindow),
        api(6) {
    ui->setupUi(this);
    setupTapeWidget();
}

TMMainWindow::~TMMainWindow() {
    delete ui;
}

void TMMainWindow::setupTapeWidget() {
    ui->tapeWidget->setColumnCount(TAPELENGTH);
    ui->tapeWidget->setRowCount(1);
}
