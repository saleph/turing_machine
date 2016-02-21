#include "GraphTableWidget.h"

void GraphTableWidget::keyPressEvent(QKeyEvent *key) {
    handleAddingAndRemovingRows(key);
    return QTableWidget::keyPressEvent(key);
}

void GraphTableWidget::handleAddingAndRemovingRows(QKeyEvent *key) {
    if (isEnterOrReturnKey(key)) {
        handleEnterReturnKey();
    } else if (isBackspaceOrDelKey(key)) {
        handleBackspaceDelKey();
    }
}

bool GraphTableWidget::isEnterOrReturnKey(QKeyEvent *key) const {
    return (key->key() == Qt::Key_Enter || key->key() == Qt::Key_Return);
}

void GraphTableWidget::handleEnterReturnKey() {
    insertNewRowAfterCurrent();
    setCurrentRowToNextRow();
    updateRowsLabels();
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
    return (key->key() == Qt::Key_Backspace || key->key() == Qt::Key_Delete);
}

void GraphTableWidget::handleBackspaceDelKey() {
    if (isCurrentRowEmpty()) {
        if (isRowCountGreaterThan1()) {
            processRemovingRow();
        } else { // if row count == 1, process event normally
            return; // back to keyPressEvent
        }
    } else { // if row is not empty, process event normally
        return; // back to keyPressEvent
    }
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

void GraphTableWidget::processRemovingRow() {
    int rowToRemove = this->currentRow();
    setCurrentRowAfterRemove();
    removeRow(rowToRemove);
    updateRowsLabels();
}

void GraphTableWidget::setCurrentRowAfterRemove() {
    int currentRow = this->currentRow();
    if (isLastRow(currentRow)) {
        setCurrentRowToPreviousRow();
    } else {
        setCurrentRowToNextRow();
    }
}

bool GraphTableWidget::isLastRow(const int row) const {
    return row == (this->rowCount() - 1);
}
