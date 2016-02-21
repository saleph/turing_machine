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
}
