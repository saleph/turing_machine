#include "tmtapemodel.h"

TMTapeModel::TMTapeModel(QObject *parent, std::shared_ptr<TMTape> tapePtr)
    : QAbstractTableModel(parent), tape(tapePtr)
{
    tape->installTapeEditNotifier([this](size_t pos) {
        QModelIndex idx = index(0, pos);
        emit dataChanged(idx, idx, QVector<int>() << Qt::DisplayRole);
    });
}

//QVariant TMTapeModel::headerData(int section, Qt::Orientation orientation, int role) const
//{
//    // FIXME: Implement me!
//}

//bool TMTapeModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
//{
//    if (value != headerData(section, orientation, role)) {
//        // FIXME: Implement me!
//        emit headerDataChanged(orientation, section, section);
//        return true;
//    }
//    return false;
//}

int TMTapeModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return 1;
}


int TMTapeModel::columnCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return tape->size();
}

QVariant TMTapeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole) {
        auto pos = index.column();
        return QVariant(QString(tape->at(pos)));
    }
    return QVariant();
}

bool TMTapeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {
        // FIXME: Implement me!
        auto pos = index.column();
        tape->at(pos) = value.toString().at(0).toLatin1();
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags TMTapeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable | Qt::ItemIsSelectable | QAbstractTableModel::flags(index);
}
