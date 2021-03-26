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

QString Monster::getUuid_m() const
{
    return uuid_m;
}

Profile::Profile()
{

}

void Profile::loadProfile(QJsonDocument &doc)
{
    QJsonObject obj = doc.object();

    //  Load Monsters
    //
    QJsonArray monArray = obj["monsters"].toArray();
    foreach (const QJsonValue &value, monArray)
    {
        addMonster(value.toObject());
//        Monster *mon = new Monster(value.toObject());
//        monsters_m.push_back(mon);
    }

    //  Load Teams
    //
    QJsonArray teamArray = obj["teams"].toArray();
    foreach (const QJsonValue &value, teamArray)
    {
        Team *team = new Team(value.toObject());
        QJsonArray uuids = value.toObject()["uuids"].toArray();
        foreach (Monster *mon, monsters_m)
        {
            if (uuids.contains(mon->getUuid_m()))
                team->addMonster(mon);
        }
    }
}

int Profile::monstersSize()
{
    return monsters_m.size();
}

void Profile::addMonster(const QJsonObject &monsterData)
{
    QNetworkRequest request;
    QNetworkAccessManager networkManager;
    QUrl url = QUrl(QString("https://swarfarm.com/static/herders/images/monsters/"));
    url.setPath(QString("%1%2").arg(url.path()).arg(monsterData["imagePath"].toString()));
    request.setUrl(url);
    QNetworkReply *reply = networkManager.get(request);

    //  Not the most optimal method
    //  Change later
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), &loop, SLOT(quit()));
    loop.exec();

    QByteArray bytes = reply->readAll();
    QImage image;
    image.loadFromData(bytes);
    Monster *mon = new Monster(monsterData, image);
    monsters_m.push_back(mon);

}
