#include "GraphTableWidget.h"

void GraphTableWidget::keyPressEvent(QKeyEvent *key) {
    if (isEnterOrReturnKey(key)) {
        insertNewRowAfterCurrent();
        setCurrentRowToNextRow();
        updateRowsLabels();
    } else if (isBackspaceOrDelKey(key)) {
        if (isCurrentRowEmpty()) {
            int rowToRemove = this->currentRow();
            if (isBackspaceKey(key)) {
                setCurrentRowToPreviousRow();
            } else if (isDelKey(key)) {
                setCurrentRowToNextRow();
            }
            if (isRowCountGreaterThan1()) {
                removeRow(rowToRemove);
                updateRowsLabels();
            }
        } else { // if row is not empty, process event normally
            return QTableWidget::keyPressEvent(key);
        }
    }
    return QTableWidget::keyPressEvent(key);
}

bool GraphTableWidget::isEnterOrReturnKey(QKeyEvent *key) const {
    return (key->key() == Qt::Key_Enter || key->key() == Qt::Key_Return);
}

void GraphTableWidget::insertNewRowAfterCurrent() {
    int currentRow = this->currentRow();
    this->insertRow(currentRow + 1);
}

void GraphTableWidget::setCurrentRowToNextRow() {
    int currentRow = this->currentRow();
    this->setCurrentCell(currentRow + 1, 0);
}

void GraphTableWidget::updateRowsLabels() {
    for (int i = 0; i < this->rowCount(); i++) {
        QString newRowHeaderName = QString::number(i + 1) + '.';
        this->setVerticalHeaderItem(i, new QTableWidgetItem(newRowHeaderName));
    }
}

bool GraphTableWidget::isBackspaceOrDelKey(QKeyEvent *key) const {
    return isBackspaceKey(key) || isDelKey(key);
}

bool GraphTableWidget::isBackspaceKey(QKeyEvent *key) const {
    return key->key() == Qt::Key_Backspace;
}

bool GraphTableWidget::isDelKey(QKeyEvent *key) const {
    return key->key() == Qt::Key_Delete;
}

bool GraphTableWidget::isCurrentRowEmpty() const {
    int currentRow = this->currentRow();
    QTableWidgetItem *currentItem = this->item(currentRow, 0);
    return (!currentItem || currentItem->text().isEmpty());
}

void GraphTableWidget::setCurrentRowToPreviousRow() {
    int currentRow = this->currentRow();
    this->setCurrentCell(currentRow - 1, 0);
}

bool GraphTableWidget::isRowCountGreaterThan1() const {
    return this->rowCount() > 1;
}
