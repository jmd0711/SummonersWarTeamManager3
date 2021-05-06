#include "boxmenu.h"
#include "ui_boxmenu.h"

BoxMenu::BoxMenu(MonsterListModel *mLM, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BoxMenu),
    mListModel{ mLM }
{
    ui->setupUi(this);

    t = MonsterDisplay::DELETE;
    proxyModel = new MonsterFilterProxyModel(this);

    listView = new QListView(this);
    listView->setViewMode(QListView::IconMode);
    listView->setFlow(QListView::LeftToRight);
    //listView->setResizeMode(QListView::Adjust);
    listView->setTextElideMode(Qt::ElideRight);
    listView->setGridSize(QSize(128, 135));
    //listView->setItemAlignment(Qt::AlignLeft);
    ui->verticalLayout->addWidget(listView);

    //  TODO:   sorting and filtering

    //proxyModel->setSourceModel(proxyModel);
    //proxyModel->sort(-1);

    //QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(mListModel);
    proxyModel->setDynamicSortFilter(true);
    listView->setModel(proxyModel);

    ui->comboBox->addItem("Monster id");
    ui->comboBox->addItem("Name");
    ui->comboBox->addItem("Priority");

    connect(listView, &QListView::clicked, this, &BoxMenu::monsterSelected);

    addProfile = new Profile();
    addListModel = new MonsterListModel(addProfile, this);
}

BoxMenu::~BoxMenu()
{
    delete ui;
}

void BoxMenu::monsterSelected(const QModelIndex &proxyIndex)
{
    QModelIndex index = proxyModel->mapToSource(proxyIndex);
    Monster *monster = mListModel->data(index, Qt::UserRole).value<Monster*>();
    MonsterDisplay monDisplay(t);
    monDisplay.editContents(monster);

    switch (monDisplay.exec())
    {
    case MonsterDisplay::ADD:
        emit addSelected(monster);
        //  ADD is only used in a QDialog request;
        qobject_cast<QDialog*>(this->parent())->close();
        break;
    case MonsterDisplay::DELETE:
        mListModel->removeRow(index.row());
        break;
    case MonsterDisplay::EDIT:
    {
        QVariant mon = QVariant::fromValue(monDisplay.getDataChange());
        mListModel->setData(index, mon, Qt::EditRole);
        break;
    }
    default:
        break;
    }
}

void BoxMenu::onMonstersReceived(QNetworkReply *reply)
{
    addListModel->clearProfileMonsters();

    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject obj = doc.object();
    QJsonArray array = obj["results"].toArray();

    foreach (const QJsonValue &value, array)
    {
        QJsonObject importedObject = value.toObject();

        QJsonObject monsterJson;
        monsterJson.insert("accuracy", importedObject["accuracy"].toInt());
        monsterJson.insert("attack", importedObject["max_lvl_attack"].toInt());
        monsterJson.insert("awakened", !importedObject["awaken_lvl"].toBool());
        monsterJson.insert("criticalDamage", importedObject["crit_damage"].toInt());
        monsterJson.insert("criticalRate", importedObject["crit_rate"].toInt());
        monsterJson.insert("defense", importedObject["max_lvl_defense"].toInt());
        monsterJson.insert("description", "");
        monsterJson.insert("element", importedObject["element"].toString());
        monsterJson.insert("hp", importedObject["max_lvl_hp"].toInt());
        monsterJson.insert("id", importedObject["id"].toInt());
        monsterJson.insert("imagePath", importedObject["image_filename"].toString());
        monsterJson.insert("level", 40);
        monsterJson.insert("name", importedObject["name"].toString());
        monsterJson.insert("priority", 0);
        monsterJson.insert("resistance", importedObject["resistance"].toInt());
        monsterJson.insert("speed", importedObject["speed"].toInt());
        monsterJson.insert("stars",importedObject["natural_stars"].toInt());
        monsterJson.insert("uuid", QUuid::createUuid().toString());

        Monster *monster = new Monster(monsterJson);
        addListModel->addRow(monster);
        //requestData(monsterJson);
    }
    reply->close();
    reply->deleteLater();
    QObject *networkManager = sender();
    networkManager->deleteLater();

    //  TODO make a new class request menu
    QDialog *requestWindow = new QDialog(this);
    requestWindow->resize(QDesktopWidget().availableGeometry(this).size() * 0.7);
    QVBoxLayout *requestLayout = new QVBoxLayout(requestWindow);
    //  TODO change mListModel to new profile
    BoxMenu *requestMenu = new BoxMenu(addListModel, requestWindow);
    requestMenu->setTask(MonsterDisplay::ADD);

    requestWindow->setLayout(requestLayout);
    requestWindow->layout()->addWidget(requestMenu);
    connect(requestMenu, &BoxMenu::addSelected, this, &BoxMenu::addSelectedMonster);
    requestWindow->exec();
}

MonsterDisplay::Task BoxMenu::getTask() const
{
    return t;
}

void BoxMenu::setTask(const MonsterDisplay::Task &value)
{
    t = value;
}

void BoxMenu::enableAddButton(bool isEnabled)
{
    ui->addButton->setEnabled(isEnabled);
}

void BoxMenu::addSelectedMonster(Monster *monster)
{
    Monster *newMonster = new Monster(*monster);
    mListModel->addRow(newMonster);
}


void BoxMenu::on_comboBox_currentTextChanged(const QString &arg1)
{
    //  sorts twice to force a sort when "lessThan" method is changed. NOT INTENDED AND NEEDS FIX
    //  TODO:   Fix
    if (arg1 == "Name")
    {
        proxyModel->setSortBy(MonsterFilterProxyModel::NAME);
        proxyModel->sort(0, Qt::DescendingOrder);
        proxyModel->sort(0, Qt::AscendingOrder);
    }
    else if (arg1 == "Priority")
    {
        proxyModel->setSortBy(MonsterFilterProxyModel::PRIORITY);
        proxyModel->sort(0, Qt::AscendingOrder);
        proxyModel->sort(0, Qt::DescendingOrder);
    }
    else
    {
        proxyModel->setSortBy(MonsterFilterProxyModel::DEFAULT);
        proxyModel->sort(0, Qt::DescendingOrder);
        proxyModel->sort(0, Qt::AscendingOrder);
    }

    //listView->reset();
}

void BoxMenu::on_lineEdit_textChanged(const QString &arg1)
{
    proxyModel->setFilterRegExp(QRegExp(arg1, Qt::CaseInsensitive, QRegExp::FixedString));
}

void BoxMenu::on_addButton_released()
{
    QString searchName = QInputDialog::getText(this, "Search Monster", "What monster do you want to add?");

    QNetworkRequest request;
    QNetworkAccessManager *networkManager = new QNetworkAccessManager(this);
    connect(networkManager, &QNetworkAccessManager::finished, this, &BoxMenu::onMonstersReceived);
    QUrl url = QUrl("https://swarfarm.com/api/v2/monsters/");
    QUrlQuery query;
    query.addQueryItem("name", searchName);
    url.setQuery(query.query());
    request.setUrl(url);
    networkManager->get(request);
}
