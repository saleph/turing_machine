#ifndef GRAPHTABLEWIDGET_H
#define GRAPHTABLEWIDGET_H

#include <QTableWidget>
#include <QKeyEvent>

class GraphTableWidget : public QTableWidget
{
    Q_OBJECT

public:
    GraphTableWidget(QWidget*& qWidget) : QTableWidget(qWidget) {}

    void updateRowsLabels();

protected:
    void keyPressEvent(QKeyEvent *key);

private:
    void handleAddingAndRemovingRows(QKeyEvent *key);
    bool isEnterOrReturnKey(QKeyEvent *key) const;
    void handleEnterReturnKey();
    void insertNewRowAfterCurrent();
    void setCurrentRowToNextRow();
    bool isBackspaceOrDelKey(QKeyEvent *key) const;
    void handleBackspaceDelKey();
    bool isCurrentRowEmpty() const;
    void setCurrentRowToPreviousRow();
    bool isRowCountGreaterThan1() const;
    void processRemovingRow();
    void setCurrentRowAfterRemove();
    bool isLastRow(const int row) const;
};

#endif // GRAPHTABLEWIDGET_H
