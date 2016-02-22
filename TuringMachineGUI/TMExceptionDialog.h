#ifndef TMEXCEPTIONDIALOG_H
#define TMEXCEPTIONDIALOG_H

#include <QDialog>

namespace Ui {
class TMExceptionDialog;
}

class TMExceptionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TMExceptionDialog(QWidget *parent = 0, const QString& errorDescription = "Unknown error!");
    ~TMExceptionDialog();

private:
    Ui::TMExceptionDialog *ui;
};

#endif // TMEXCEPTIONDIALOG_H
