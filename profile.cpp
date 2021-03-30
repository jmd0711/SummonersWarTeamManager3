#include "profile.h"

Team::Team(const QJsonObject &newTeam)
{
    area_m = newTeam["battle"].toString();
    teamName_m = newTeam["name"].toString();
    teamDescription_m = newTeam["description"].toString();
}

Team::Team(QString teamArea) :
    area_m{ teamArea }
{
    teamName_m = "New Team";
    teamDescription_m = "";
}

Team::~Team()
{
    foreach (Monster *mon, monsters_m)
    {
        removeMonster(mon);
    }
}

void Team::addMonster(Monster *monster)
{
    monsters_m.push_back(monster);
    monster->addTeam(this);
}

void Team::removeMonster(Monster *monster)
{
    monsters_m.erase(std::remove(monsters_m.begin(), monsters_m.end(), monster), monsters_m.end());
    monster->removeTeam(this);
}

Monster::Monster(const QJsonObject &newMonster, QImage image)
    : image_m(image)
{
    accuracy_m = newMonster["accuracy"].toInt();
    attack_m = newMonster["attack"].toInt();
    awakened_m = newMonster["awakened"].toBool();
    critDamage_m = newMonster["criticalDamage"].toInt();
    critRate_m = newMonster["criticalRate"].toInt();
    defense_m = newMonster["defense"].toInt();
    description_m = newMonster["description"].toString();
    element_m = newMonster["element"].toString();
    hp_m = newMonster["hp"].toInt();
    id_m = newMonster["id"].toInt();
    imagePath_m = newMonster["imagePath"].toString();
    level_m = newMonster["level"].toInt();
    name_m = newMonster["name"].toString();
    priority_m = newMonster["priority"].toInt();
    resistance_m = newMonster["resistance"].toInt();
    speed_m = newMonster["speed"].toInt();
    stars_m = newMonster["stars"].toInt();
    uuid_m = newMonster["uuid"].toString();
}

Monster::Monster()
{
    accuracy_m = 0;
    attack_m = 0;
    awakened_m = false;
    critDamage_m = 0;
    critRate_m = 0;
    defense_m = 0;
    description_m = "";
    element_m = "";
    hp_m = 0;
    id_m = 0;
    imagePath_m = "";
    level_m = 0;
    name_m = "";
    priority_m = 0;
    resistance_m = 0;
    speed_m = 0;
    stars_m = 0;
    uuid_m = "";
}

Monster::~Monster()
{
    foreach (Team *team, teams_m)
    {
        team->removeMonster(this);
    }
}

void Monster::addTeam(Team *team)
{
    teams_m.push_back(team);
}

void Monster::removeTeam(Team *team)
{
    teams_m.erase(std::remove(teams_m.begin(), teams_m.end(), team), teams_m.end());
}

int Monster::getStars() const
{
    return stars_m;
}

void Monster::setStars(int value)
{
    stars_m = value;
}

int Monster::getSpeed() const
{
    return speed_m;
}

void Monster::setSpeed(int value)
{
    speed_m = value;
}

int Monster::getResistance() const
{
    return resistance_m;
}

void Monster::setResistance(int value)
{
    resistance_m = value;
}

int Monster::getPriority() const
{
    return priority_m;
}

void Monster::setPriority(int value)
{
    priority_m = value;
}

QString Monster::getName() const
{
    return name_m;
}

void Monster::setName(const QString &value)
{
    name_m = value;
}

int Monster::getLevel() const
{
    return level_m;
}

void Monster::setLevel(int value)
{
    level_m = value;
}

QString Monster::getImagePath() const
{
    return imagePath_m;
}

int Monster::getId() const
{
    return id_m;
}

int Monster::getHp() const
{
    return hp_m;
}

void Monster::setHp(int value)
{
    hp_m = value;
}

QString Monster::getElement() const
{
    return element_m;
}

QString Monster::getDescription() const
{
    return description_m;
}

void Monster::setDescription(const QString &value)
{
    description_m = value;
}

int Monster::getDefense() const
{
    return defense_m;
}

void Monster::setDefense(int value)
{
    defense_m = value;
}

int Monster::getCritRate() const
{
    return critRate_m;
}

void Monster::setCritRate(int value)
{
    critRate_m = value;
}

int Monster::getCritDamage() const
{
    return critDamage_m;
}

void Monster::setCritDamage(int value)
{
    critDamage_m = value;
}

bool Monster::isAwakened() const
{
    return awakened_m;
}

int Monster::getAttack() const
{
    return attack_m;
}

void Monster::setAttack(int value)
{
    attack_m = value;
}

int Monster::getAccuracy() const
{
    return accuracy_m;
}

void Monster::setAccuracy(int value)
{
    accuracy_m = value;
}

QString Monster::getUuid() const
{
    return uuid_m;
}

QImage Monster::getImage() const
{
    return image_m;
}

Profile::Profile()
{
}

//void Profile::loadProfile(QJsonDocument &doc)
//{
//    QJsonObject obj = doc.object();

//    //  Load Monsters
//    //
//    QJsonArray monArray = obj["monsters"].toArray();
//    foreach (const QJsonValue &value, monArray)
//    {
//        addMonster(value.toObject());
////        Monster *mon = new Monster(value.toObject());
////        monsters_m.push_back(mon);
//    }

//    //  Load Teams
//    //
//    QJsonArray teamArray = obj["teams"].toArray();
//    foreach (const QJsonValue &value, teamArray)
//    {
//        Team *team = new Team(value.toObject());
//        QJsonArray uuids = value.toObject()["uuids"].toArray();
//        foreach (Monster *mon, monsters_m)
//        {
//            if (uuids.contains(mon->getUuid()))
//                team->addMonster(mon);
//        }
//    }
//}

int Profile::monstersSize()
{
    return monsters_m.size();
}

void Profile::addMonster(Monster* mon)
{
    monsters_m.insert(monsters_m.size(), mon);
}

void Profile::removeMonsterAt(int index)
{
    monsters_m.removeAt(index);
}

Monster* Profile::getMonster(int index) const
{
    if (index < monsters_m.size())
        return monsters_m.at(index);
    else
        return nullptr;
}

QJsonDocument Profile::getJson() const
{
    QJsonObject saveObject;

    QJsonArray monstersJsonArray;
    foreach (Monster *mon, monsters_m)
    {
        QJsonObject monsterJson;
        monsterJson.insert("accuracy", mon->getAccuracy());
        monsterJson.insert("attack", mon->getAttack());
        monsterJson.insert("awakened", mon->isAwakened());
        monsterJson.insert("criticalDamage", mon->getCritDamage());
        monsterJson.insert("criticalRate", mon->getCritRate());
        monsterJson.insert("defense", mon->getDefense());
        monsterJson.insert("description", mon->getDescription());
        monsterJson.insert("element", mon->getElement());
        monsterJson.insert("hp", mon->getHp());
        monsterJson.insert("id", mon->getId());
        monsterJson.insert("imagePath", mon->getImagePath());
        monsterJson.insert("level", mon->getLevel());
        monsterJson.insert("name", mon->getName());
        monsterJson.insert("priority", mon->getPriority());
        monsterJson.insert("resistance", mon->getResistance());
        monsterJson.insert("speed", mon->getSpeed());
        monsterJson.insert("stars", mon->getStars());
        monsterJson.insert("uuid", mon->getUuid());

        monstersJsonArray.push_back(monsterJson);
    }
    saveObject.insert("monsters", monstersJsonArray);

//    QJsonArray teamsJsonArray;
//    foreach (Team *team, teams_m)
//    {
//        QJsonObject teamJson;
//        teamJson.insert("battle", team->getBattle());
//        teamJson.insert("name", team->getTeamName());
//        teamJson.insert("description", team->getTeamDescription());
//        QJsonArray indexesJsonArray;
//        foreach (int x, team->getMonsterIndexes())
//        {
//            indexesJsonArray.push_back(x);
//        }
//        teamJson.insert("indexes", indexesJsonArray);
//        teamsJsonArray.push_back(teamJson);
//    }
//    saveObject.insert("teams", teamsJsonArray);
    QJsonDocument doc(saveObject);
    return doc;
}

//void Profile::addMonster(const QJsonObject &monsterData)
//{
//    QNetworkRequest request;
//    QNetworkAccessManager networkManager;
//    QUrl url = QUrl(QString("https://swarfarm.com/static/herders/images/monsters/"));
//    url.setPath(QString("%1%2").arg(url.path()).arg(monsterData["imagePath"].toString()));
//    request.setUrl(url);
//    QNetworkReply *reply = networkManager.get(request);

//    //  Not the most optimal method
//    //  Change later
//    QEventLoop loop;
//    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
//    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), &loop, SLOT(quit()));
//    loop.exec();

//    QByteArray bytes = reply->readAll();
//    QImage image;
//    image.loadFromData(bytes);
//    Monster *mon = new Monster(monsterData, image);
//    monsters_m.push_back(mon);

//}
