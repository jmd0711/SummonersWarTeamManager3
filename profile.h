#ifndef PROFILE_H
#define PROFILE_H

#include <QEventLoop>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>
#include <QImage>

class Monster;

class Team
{
public:
    Team(const QJsonObject &newTeam);
    Team(QString teamArea);
    ~Team();

    void addMonster(Monster *monster);
    void removeMonster(Monster *monster);

private:
    QString area_m;
    QString teamName_m;
    QString teamDescription_m;
    QVector<Monster *> monsters_m;
};

class Monster
{
public:
    Monster(const QJsonObject &newMonster, QImage image);
    ~Monster();

    friend void Team::addMonster(Monster *monster);
    friend void Team::removeMonster(Monster *monster);

    QString getUuid() const;

    QString getName() const;

    QImage getImage() const;

private:
    void addTeam(Team *team);
    void removeTeam(Team *team);

    QImage  image_m;
    QString name_m;
    QString imagePath_m;
    QString element_m;
    QString description_m;
    QString uuid_m;
    bool    awakened_m;
    int     id_m;
    int     stars_m;
    int     level_m;
    int     hp_m;
    int     attack_m;
    int     defense_m;
    int     speed_m;
    int     critRate_m;
    int     critDamage_m;
    int     resistance_m;
    int     accuracy_m;
    int     priority_m;

    QVector<Team *> teams_m;
};

class Profile : public QObject
{
    Q_OBJECT
public:
    Profile();
    //~Profile();

    //void loadProfile(QJsonDocument &doc);

    int monstersSize();

    void addMonster(Monster* mon);
    void removeMonsterAt(int index);

    Monster* getMonster(int index) const;

private:
    QVector<Monster *> monsters_m;
    QVector<Team *> teams_m;

    //void addMonster(const QJsonObject &monsterData);
};

#endif // PROFILE_H
