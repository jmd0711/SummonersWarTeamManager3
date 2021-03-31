#ifndef TEAMMENUITEMDELEGATE_H
#define TEAMMENUITEMDELEGATE_H

#include <QItemDelegate>
#include <QObject>

#include "profile.h"

class TeamMenuItemDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    TeamMenuItemDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // TEAMMENUITEMDELEGATE_H
