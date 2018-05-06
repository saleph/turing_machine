#ifndef TMTAPEMODEL_H
#define TMTAPEMODEL_H

#include <QAbstractListModel>
#include <TMTape.h>
#include <memory>
#include <QModelIndex>

class TMTapeModel : public QAbstractTableModel
{
    Q_OBJECT

    std::shared_ptr<TMTape> tape;
public:
    explicit TMTapeModel(QObject *parent = nullptr, std::shared_ptr<TMTape> tapePtr = nullptr);

    // Header:
//    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

//    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

private:
};

#endif // TMTAPEMODEL_H
