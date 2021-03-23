#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "teammanager.h"

MainMenu::MainMenu(TeamManager *parent) :
    QWidget(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);

    //  Hard Coded for now
    //
    connect(ui->arenaButton, &QPushButton::released, [parent]() {
        parent->setPage(2);
    });
    connect(ui->guildButton, &QPushButton::released, [parent]() {
        parent->setPage(5);
    });
    connect(ui->siegeButton, &QPushButton::released, [parent]() {
        parent->setPage(8);
    });
    connect(ui->tartarusButton, &QPushButton::released, [parent]() {
        parent->setPage(11);
    });
    connect(ui->cairosButton, &QPushButton::released, [parent]() {
        parent->setPage(12);
    });
    connect(ui->dimensionalButton, &QPushButton::released, [parent]() {
        parent->setPage(24);
    });
    connect(ui->riftButton, &QPushButton::released, [parent]() {
        parent->setPage(28);
    });
    connect(ui->towerButton, &QPushButton::released, [parent]() {
        parent->setPage(35);
    });
}

MainMenu::~MainMenu()
{
    delete ui;
}
