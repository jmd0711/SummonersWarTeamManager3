#ifndef TEAMMENU_H
#define TEAMMENU_H

#include <QWidget>

#include "profile.h"
//#include "team.h"
//#include "teamlistview.h"

namespace Ui {
class TeamMenu;
}

class TeamMenu : public QWidget
{
    Q_OBJECT

public:
    explicit TeamMenu(Profile *pr, QString name, QWidget *parent = nullptr);
    ~TeamMenu();

private slots:
    void on_addButton_released();

private:
    Ui::TeamMenu *ui;

    Profile *profile;

    QString battleName;

//    TeamListView *teamListWidget;
};

#endif // TEAMMENU_H
