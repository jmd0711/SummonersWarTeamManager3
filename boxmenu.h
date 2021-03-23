#ifndef BOXMENU_H
#define BOXMENU_H

#include <QWidget>

//#include "monsterlistview.h"
#include "profile.h"

namespace Ui {
class BoxMenu;
}

class BoxMenu : public QWidget
{
    Q_OBJECT

public:
    explicit BoxMenu(Profile *pr, QWidget *parent = nullptr);
    ~BoxMenu();

private:
    Ui::BoxMenu *ui;

    Profile *profile;

//    MonsterListView *monsterListWidget;
};

#endif // BOXMENU_H
