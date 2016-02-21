#ifndef GRAPHTABLEWIDGET_H
#define GRAPHTABLEWIDGET_H

#include <QTableWidget>
#include <QKeyEvent>

class GraphTableWidget : public QTableWidget
{
    Q_OBJECT

public:
    GraphTableWidget(QWidget*& qWidget) : QTableWidget(qWidget) {}

protected:
    void keyPressEvent(QKeyEvent *key);

private:
    bool isEnterOrReturnKey(QKeyEvent *key) const;
    void insertNewRowAfterCurrent();
    void setCurrentRowToNextRow();
    void updateRowsLabels();
    bool isBackspaceOrDelKey(QKeyEvent *key) const;
    bool isBackspaceKey(QKeyEvent *key) const;
    bool isDelKey(QKeyEvent *key) const;
    bool isCurrentRowEmpty() const;
    void setCurrentRowToPreviousRow();
    bool isRowCountGreaterThan1() const;
};

#endif // GRAPHTABLEWIDGET_H
