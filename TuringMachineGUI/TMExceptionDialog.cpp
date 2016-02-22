#include "TMExceptionDialog.h"
#include "ui_TMExceptionDialog.h"

TMExceptionDialog::TMExceptionDialog(QWidget *parent, const QString &errorDescription) :
        QDialog(parent),
        ui(new Ui::TMExceptionDialog) {
    ui->setupUi(this);
    ui->errorDescription->setText(errorDescription);
}

TMExceptionDialog::~TMExceptionDialog() {
    delete ui;
}
