#include "boxmenu.h"
#include "ui_boxmenu.h"

BoxMenu::BoxMenu(Profile *pr, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BoxMenu),
    profile(pr)
{
    ui->setupUi(this);

//    monsterListWidget = new MonsterListView(profile, MonsterListView::BOX, this);
//    ui->scrollArea->setWidgetResizable(true);
//    ui->scrollArea->setWidget(monsterListWidget);
}

BoxMenu::~BoxMenu()
{
    delete ui;
}
