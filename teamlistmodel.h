#ifndef TEAMLISTMODEL_H
#define TEAMLISTMODEL_H

#include <QAbstractItemModel>

#include "profile.h"

class TeamListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit TeamListModel(Profile *pr, QObject *parent = nullptr);

    // Basic functionality:

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    // Add data:
    bool addRow(Team *team);

    // Remove data:
    bool removeRow(int row);

private:
    Profile *profile;
};

#endif // TEAMLISTMODEL_H
