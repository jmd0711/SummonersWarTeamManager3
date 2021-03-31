#ifndef TEAMMENU_H
#define TEAMMENU_H

#include <QListView>
#include <QSortFilterProxyModel>
#include <QWidget>

#include "profile.h"
#include "teamdisplay.h"
#include "teamlistmodel.h"
#include "teammenuitemdelegate.h"

namespace Ui {
class TeamMenu;
}

class TeamMenu : public QWidget
{
    Q_OBJECT

public:
    explicit TeamMenu(TeamListModel *tLM, QString name, QWidget *parent = nullptr);
    ~TeamMenu();

private slots:
    void teamSelected(const QModelIndex &index);

    void on_addButton_released();

private:
    Ui::TeamMenu *ui;

    QString battleName;

    TeamListModel *tListModel;
    TeamMenuItemDelegate *tDelegate;
};

#endif // TEAMMENU_H
