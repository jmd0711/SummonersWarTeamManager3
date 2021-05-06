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

    profile = new Profile();
    mListModel = new MonsterListModel(profile, this);
    tListModel = new TeamListModel(profile, this);

    setWindowTitle("Summoners War Team Manager V3.0");
    layout = new QStackedLayout();

    menuPage = new MainMenu(this);
    boxPage = new BoxMenu(mListModel, this);
    boxPage->enableAddButton(true);
    layout->addWidget(menuPage);
    layout->addWidget(boxPage);

    int nextPos;
    QVector<QString> arenaNames = {"Arena Offense", "Arena Defense"}; //2
    nextPos = layout->count();
    arenaPage = new AreaMenu(nextPos, arenaNames, this);
    layout->addWidget(arenaPage);
    foreach (QString battleName, arenaNames)
        layout->addWidget(new TeamMenu(mListModel, tListModel, battleName, this));

    QVector<QString> guildNames = {"Guild Offense", "Guild Defense"}; //5
    nextPos = layout->count();
    guildPage = new AreaMenu(layout->count(), guildNames, this);
    layout->addWidget(guildPage);
    foreach (QString battleName, guildNames)
        layout->addWidget(new TeamMenu(mListModel, tListModel, battleName, this));

    QVector<QString> siegeNames = {"Siege Offense", "Siege Defense"}; //8
    nextPos = layout->count();
    siegePage = new AreaMenu(layout->count(), siegeNames, this);
    layout->addWidget(siegePage);
    foreach (QString battleName, siegeNames)
        layout->addWidget(new TeamMenu(mListModel, tListModel, battleName, this));

    tartarusPage = new TeamMenu(mListModel, tListModel, "Tartarus Labyrinth", this);  //  Not an AreaMenu //11
    layout->addWidget(tartarusPage);

    QVector<QString> cairosNames = {"Giants", "Dragons", "Necropolis", "Steel Fortress", "Punisher's Crypt",
                                   "Hall of Magic", "Hall of Light", "Hall of Dark", "Hall of Fire", "Hall of Water", "Hall of Wind"};
    nextPos = layout->count();                                                      //12
    cairosPage = new AreaMenu(layout->count(), cairosNames, this);
    layout->addWidget(cairosPage);
    foreach (QString battleName, cairosNames)
        layout->addWidget(new TeamMenu(mListModel, tListModel, battleName, this));

    QVector<QString> dimensionalNames = {"Karzhan", "Ellunia", "Lumel"}; //24
    nextPos = layout->count();
    dimensionalPage = new AreaMenu(layout->count(), dimensionalNames, this);
    layout->addWidget(dimensionalPage);
    foreach (QString battleName, dimensionalNames)
        layout->addWidget(new TeamMenu(mListModel, tListModel, battleName, this));

    QVector<QString> riftNames = {"Rift Raid", "Light Beast", "Dark Beast", "Fire Beast", "Water Beast", "Wind Beast"}; //28
    nextPos = layout->count();
    riftPage = new AreaMenu(layout->count(), riftNames, this);
    layout->addWidget(riftPage);
    foreach (QString battleName, riftNames)
        layout->addWidget(new TeamMenu(mListModel, tListModel, battleName, this));

    towerPage = new TeamMenu(mListModel, tListModel, "Tower of Ascension", this); //  Not an AreaMenu //35
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
    filePath = "";
    clearProfile();
}

void TeamManager::on_actionOpen_triggered()
{
    QString filter = "JSON File (*.json)";
    QString newFilePath = QFileDialog::getOpenFileName(this, "Open Profile", "", filter);
    QFile file(newFilePath);
    filePath = newFilePath;
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "..", "File Was Not Opened.");
        return;
    }
    QJsonParseError JsonParseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll(), &JsonParseError);
    file.close();

    clearProfile();

    QJsonObject obj = jsonDoc.object();

    //  Load Monsters
    //
    QJsonArray monArray = obj["monsters"].toArray();
    foreach (const QJsonValue &value, monArray)
    {
        Monster *monster = new Monster(value.toObject());
        mListModel->addRow(monster);
        //QModelIndex index = mListModel->index(mListModel->rowCount() - 1);
        //requestImage(index);
        //requestImage(monster);
    }

    //  Load Teams
    //
    QJsonArray teamArray = obj["teams"].toArray();
    foreach (const QJsonValue &value, teamArray)
    {
        Team *team = new Team(value.toObject());
        QJsonArray uuids = value.toObject()["uuids"].toArray();
        foreach (const QJsonValue &value, uuids)
        {
            foreach (Monster * monster, profile->getMonsters())
            {
                if (value.toString() == monster->getUuid())
                {
                    team->addMonster(monster);
                    break;
                }
            }
        }
        tListModel->addRow(team);
    }
}

void TeamManager::on_actionSave_triggered()
{
    QFile file(filePath);
    if (!file.open(QFile::WriteOnly | QFile::Truncate)) {
        QMessageBox::warning(this, "..", "No File Path.");
        return;
    }

    file.write(profile->getJson().toJson());
    file.flush();
    file.close();
}

void TeamManager::on_actionSave_As_triggered()
{
    QString filter = "JSON File (*.json)";
    QString newFilePath = QFileDialog::getSaveFileName(this, "Save Profile", "", filter);
    QFile file(newFilePath);
    filePath = newFilePath;
    if (!file.open(QFile::WriteOnly | QFile::Truncate)) {
        QMessageBox::warning(this, "..", "File Was Not Saved.");
        return;
    }

    file.write(profile->getJson().toJson());
    file.flush();
    file.close();
}

void TeamManager::on_actionImport_triggered()
{
    //QString profileName = QInputDialog::getText(this, "Import From Swarfarm", "What is your profile name?");
    //  TODO:  Ask to clear profile?
    ImportDialog::Task t;
    bool ok;
    QString profileName = ImportDialog::getInput(this, &t, &ok);
    if (ok)
    {
        if (t == ImportDialog::Merge)
        {
            qDebug() << "merge";
        }
        if (t == ImportDialog::New)
        {
            clearProfile();
            qDebug() << "new";
        }
        QNetworkRequest request;
        QNetworkAccessManager *networkManager = new QNetworkAccessManager(this);
        connect(networkManager, &QNetworkAccessManager::finished, this, &TeamManager::onImport);
        QUrl url = QUrl("https://swarfarm.com/api/v2/profiles/");
        url.setPath(QString("%1%2/monsters/").arg(url.path()).arg(profileName));
        request.setUrl(url);
        networkManager->get(request);
    }
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

void TeamManager::onImport(QNetworkReply *reply)
{
    // ADD Error Check Here
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject obj = doc.object();
    QJsonArray array = obj["results"].toArray();

    foreach (const QJsonValue &value, array)
    {
//        Monster *mon = new Monster(value.toObject(), Monster::IMPORT);
//        addMonster(mon);
        QJsonObject importedObject = value.toObject();

        QJsonObject monsterJson;
        monsterJson.insert("accuracy", importedObject["base_accuracy"].toInt() + importedObject["rune_accuracy"].toInt());
        monsterJson.insert("attack", importedObject["base_attack"].toInt() + importedObject["rune_attack"].toInt());
        monsterJson.insert("criticalDamage", importedObject["base_crit_damage"].toInt() + importedObject["rune_crit_damage"].toInt());
        monsterJson.insert("criticalRate", importedObject["base_crit_rate"].toInt() + importedObject["rune_crit_rate"].toInt());
        monsterJson.insert("defense", importedObject["base_defense"].toInt() + importedObject["rune_defense"].toInt());
        monsterJson.insert("description", importedObject["notes"]);
        monsterJson.insert("hp", importedObject["base_hp"].toInt() + importedObject["rune_hp"].toInt());
        monsterJson.insert("id", importedObject["monster"].toInt());
        monsterJson.insert("level", importedObject["level"].toInt());
        monsterJson.insert("priority", importedObject["priority"]);
        monsterJson.insert("resistance", importedObject["base_resistance"].toInt() + importedObject["rune_resistance"].toInt());
        monsterJson.insert("speed", importedObject["base_speed"].toInt() + importedObject["rune_speed"].toInt());
        monsterJson.insert("stars",importedObject["stars"].toInt());
        monsterJson.insert("uuid", importedObject["id"].toString());

        requestData(monsterJson);
    }
    reply->close();
    reply->deleteLater();
    QObject *networkManager = sender();
    networkManager->deleteLater();
}

void TeamManager::onDataReceived(QNetworkReply *reply)
{
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject monData = doc.object();

    QJsonObject monsterJson = dataStorage[reply];

    monsterJson.insert("awakened", !monData["awaken_level"].toBool());
    monsterJson.insert("element", monData["element"].toString());
    monsterJson.insert("imagePath", monData["image_filename"].toString());
    monsterJson.insert("name", monData["name"].toString());

    Monster *monster = new Monster(monsterJson);
    if (!profile->hasUUID(monster))
        mListModel->addRow(monster);
    //QModelIndex index = mListModel->index(mListModel->rowCount() - 1);
    //requestImage(index);

    reply->close();
    reply->deleteLater();
    QObject *networkManager = sender();
    networkManager->deleteLater();
}

//void TeamManager::onImageReceived(QNetworkReply *reply)
//{
//    QByteArray bytes = reply->readAll();
//    QImage image;
//    image.loadFromData(bytes);

////    Monster *monster = mListModel->data(monsterStorage[reply], Qt::UserRole).value<Monster*>();
////    monster->setImage(image);

//    mListModel->setData(monsterStorage[reply], image, Qt::DecorationRole);

//    //Monster *mon = new Monster(monsterJson, image);

//    monsterStorage.remove(reply);

//    reply->close();
//    reply->deleteLater();
//    QObject *networkManager = sender();
//    networkManager->deleteLater();
//}

//void TeamManager::requestImage(const QModelIndex &index)
//{
//    Monster *monster = mListModel->data(index, Qt::UserRole).value<Monster*>();
//    QNetworkRequest request;
//    QNetworkAccessManager *networkManager = new QNetworkAccessManager(this);
//    QUrl url = QUrl(QString("https://swarfarm.com/static/herders/images/monsters/"));
//    url.setPath(QString("%1%2").arg(url.path()).arg(monster->getImagePath()));
//    request.setUrl(url);
//    connect(networkManager, &QNetworkAccessManager::finished, this, &TeamManager::onImageReceived);
//    QNetworkReply *reply = networkManager->get(request);
//    monsterStorage[reply] = index;
//}

void TeamManager::clearProfile()
{
    mListModel->clearProfileMonsters();
    tListModel->clearProfileTeams();
}

void TeamManager::requestData(QJsonObject &partialData)
{
    QNetworkRequest request;
    QNetworkAccessManager *networkManager = new QNetworkAccessManager(this);
    QUrl url = QUrl("https://swarfarm.com/api/v2/monsters/");
    url.setPath(QString("%1%2/").arg(url.path()).arg(partialData["id"].toInt()));
    request.setUrl(url);
    connect(networkManager, &QNetworkAccessManager::finished, this, &TeamManager::onDataReceived);
    QNetworkReply *reply = networkManager->get(request);
    dataStorage[reply] = partialData;
}

