#include "teammenu.h"
#include "ui_teammenu.h"

TeamMenu::TeamMenu(Profile *pr, QString name, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TeamMenu),
    profile{ pr },
    battleName{ name }
{
    ui->setupUi(this);
    ui->label->setText(battleName);

//    teamListWidget = new TeamListView(profile, battleName, this);
//    ui->scrollArea->setWidgetResizable(true);
//    ui->scrollArea->setWidget(teamListWidget);
//    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

TeamMenu::~TeamMenu()
{
    delete ui;
}

void TeamMenu::on_addButton_released()
{
//    profile->addTeam(new Team(battleName));
}
