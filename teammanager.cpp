#include "teammanager.h"
#include "ui_teammanager.h"

TeamManager::TeamManager(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TeamManager)
{
    ui->setupUi(this);
    resize(QDesktopWidget().availableGeometry(this).size() * 0.7);
    ui->backButton->setDisabled(true);
    ui->mainButton->setDisabled(true);

    profile = new Profile(this);

    setWindowTitle("Summoners War Team Manager V3.0");
    layout = new QStackedLayout();

    menuPage = new MainMenu(this);
    boxPage = new BoxMenu(profile, this);
    layout->addWidget(menuPage);
    layout->addWidget(boxPage);

    int nextPos;
    QVector<QString> arenaNames = {"Arena Offense", "Arena Defense"}; //2
    nextPos = layout->count();
    arenaPage = new AreaMenu(nextPos, arenaNames, this);
    layout->addWidget(arenaPage);
    foreach (QString battleName, arenaNames)
        layout->addWidget(new TeamMenu(profile, battleName, this));

    QVector<QString> guildNames = {"Guild Offense", "Guild Defense"}; //5
    nextPos = layout->count();
    guildPage = new AreaMenu(layout->count(), guildNames, this);
    layout->addWidget(guildPage);
    foreach (QString battleName, guildNames)
        layout->addWidget(new TeamMenu(profile, battleName, this));

    QVector<QString> siegeNames = {"Siege Offense", "Siege Defense"}; //8
    nextPos = layout->count();
    siegePage = new AreaMenu(layout->count(), siegeNames, this);
    layout->addWidget(siegePage);
    foreach (QString battleName, siegeNames)
        layout->addWidget(new TeamMenu(profile, battleName, this));

    tartarusPage = new TeamMenu(profile, "Tartarus Labyrinth", this);  //  Not an AreaMenu //11
    layout->addWidget(tartarusPage);

    QVector<QString> cairosNames = {"Giants", "Dragons", "Necropolis", "Steel Fortress", "Punisher's Crypt",
                                   "Hall of Magic", "Hall of Light", "Hall of Dark", "Hall of Fire", "Hall of Water", "Hall of Wind"};
    nextPos = layout->count();                                                      //12
    cairosPage = new AreaMenu(layout->count(), cairosNames, this);
    layout->addWidget(cairosPage);
    foreach (QString battleName, cairosNames)
        layout->addWidget(new TeamMenu(profile, battleName, this));

    QVector<QString> dimensionalNames = {"Karzhan", "Ellunia", "Lumel"}; //24
    nextPos = layout->count();
    dimensionalPage = new AreaMenu(layout->count(), dimensionalNames, this);
    layout->addWidget(dimensionalPage);
    foreach (QString battleName, dimensionalNames)
        layout->addWidget(new TeamMenu(profile, battleName, this));

    QVector<QString> riftNames = {"Rift Raid", "Light Beast", "Dark Beast", "Fire Beast", "Water Beast", "Wind Beast"}; //28
    nextPos = layout->count();
    riftPage = new AreaMenu(layout->count(), riftNames, this);
    layout->addWidget(riftPage);
    foreach (QString battleName, riftNames)
        layout->addWidget(new TeamMenu(profile, battleName, this));

    towerPage = new TeamMenu(profile, "Tower of Ascension", this); //  Not an AreaMenu //35
    layout->addWidget(towerPage);


    layout->setCurrentIndex(0);
    lastPageIndex = layout->currentIndex();
    ui->verticalLayout->insertLayout(0, layout);
}

TeamManager::~TeamManager()
{
    delete ui;
}

void TeamManager::setPage(int index)
{
    layout->setCurrentIndex(index);
    lastPageStack.push_back(lastPageIndex);
    lastPageIndex = layout->currentIndex();

    if (lastPageStack.isEmpty())
        ui->backButton->setDisabled(true);
    else
        ui->backButton->setDisabled(false);

    if (layout->currentIndex() == 0)
    {
        ui->mainButton->setDisabled(true);
        ui->boxButton->setDisabled(false);
    }
    else if (layout->currentIndex() == 1)
    {
        ui->mainButton->setDisabled(false);
        ui->boxButton->setDisabled(true);
    }
    else
    {
        ui->mainButton->setDisabled(false);
        ui->boxButton->setDisabled(false);
    }
}

void TeamManager::on_backButton_released()
{

    layout->setCurrentIndex(lastPageStack.last());
    lastPageIndex = lastPageStack.last();
    lastPageStack.pop_back();

    if (lastPageStack.isEmpty())
        ui->backButton->setDisabled(true);
    else
        ui->backButton->setDisabled(false);

    if (layout->currentIndex() == 0)
    {
        ui->mainButton->setDisabled(true);
        ui->boxButton->setDisabled(false);
    }
    else if (layout->currentIndex() == 1)
    {
        ui->mainButton->setDisabled(false);
        ui->boxButton->setDisabled(true);
    }
    else
    {
        ui->mainButton->setDisabled(false);
        ui->boxButton->setDisabled(false);
    }
}

void TeamManager::on_mainButton_released()
{
    ui->backButton->setDisabled(true);
    ui->mainButton->setDisabled(true);
    ui->boxButton->setDisabled(false);
    lastPageStack.clear();
    layout->setCurrentIndex(0);
    lastPageIndex = layout->currentIndex();
}

void TeamManager::on_boxButton_released()
{
    ui->backButton->setDisabled(false);
    ui->mainButton->setDisabled(false);
    ui->boxButton->setDisabled(true);
    layout->setCurrentIndex(1);
    lastPageStack.push_back(lastPageIndex);
    lastPageIndex = layout->currentIndex();
}

void TeamManager::on_actionNew_triggered()
{
//    filePath = "";
//    profile->clear();
}

void TeamManager::on_actionOpen_triggered()
{
//    QString filter = "JSON File (*.json)";
//    QString newFilePath = QFileDialog::getOpenFileName(this, "Open Profile", "", filter);
//    QFile file(newFilePath);
//    filePath = newFilePath;
//    if (!file.open(QFile::ReadOnly | QFile::Text)) {
//        QMessageBox::warning(this, "..", "File Was Not Opened.");
//        return;
//    }
//    QJsonParseError JsonParseError;
//    QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll(), &JsonParseError);
//    file.close();

//    profile->clear();
//    profile->loadProfile(jsonDoc);
}

void TeamManager::on_actionSave_triggered()
{
//    QFile file(filePath);
//    if (!file.open(QFile::WriteOnly | QFile::Truncate)) {
//        QMessageBox::warning(this, "..", "No File Path.");
//        return;
//    }

//    file.write(profile->getJsonProfile().toJson());
//    file.flush();
//    file.close();
}

void TeamManager::on_actionSave_As_triggered()
{
//    QString filter = "JSON File (*.json)";
//    QString newFilePath = QFileDialog::getSaveFileName(this, "Save Profile", "", filter);
//    QFile file(newFilePath);
//    filePath = newFilePath;
//    if (!file.open(QFile::WriteOnly | QFile::Truncate)) {
//        QMessageBox::warning(this, "..", "File Was Not Saved.");
//        return;
//    }

//    file.write(profile->getJsonProfile().toJson());
//    file.flush();
//    file.close();
}

void TeamManager::on_actionImport_triggered()
{
//    QString profileName = QInputDialog::getText(this, "Import From Swarfarm", "What is your profile name?");
//    profile->importFromSFProfile(profileName);
}

void TeamManager::on_actionAbout_triggered()
{
    QString info =  "Summoner's War Team Manager V3.0\n\n"
                    "Copyright 2021, Jasper Matthew Dumdumaya, all rights reserved.\n\n"
                    "Application is created using Qt 5.15.1 and Qt Creator 4.13.1\n\n"
                    "Images are owned by COM2US.\n"
                    "Data is gathered from SWARFARM.\n";
    QMessageBox::information(this, "About", info);
}

