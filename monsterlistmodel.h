#ifndef MONSTERLISTMODEL_H
#define MONSTERLISTMODEL_H

#include <QAbstractListModel>
#include <QPixmap>

#include "profile.h"

class MonsterListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit MonsterListModel(Profile *pr, QObject *parent = nullptr);

    // Header:
//    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

//    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    // Add data:
    bool addRow(Monster *mon);

    // Remove data:
    bool removeRow(int row);

    void clearProfileMonsters();

private slots:
    void onMonsterImageChanged(int row);
private:
    Profile *profile;
};

#endif // MONSTERLISTMODEL_H
