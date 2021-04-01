#ifndef TEAMMENU_H
#define TEAMMENU_H

#include <QDataWidgetMapper>
#include <QLineEdit>
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
    //void teamSelected(const QModelIndex &index);

    void on_addButton_released();

    void updatePage(int row);

    void on_editButton_released();

    void on_deleteButton_released();

private:
    Ui::TeamMenu *ui;

    QString battleName;

    TeamListModel *tListModel;
    QSortFilterProxyModel *proxyModel;
    //TeamMenuItemDelegate *tDelegate;

    QDataWidgetMapper *mapper;
};

#endif // TEAMMENU_H
