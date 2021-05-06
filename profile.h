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
    Team();
    ~Team();

    void addMonster(Monster *monster);
    void removeMonster(Monster *monster);

    QString getTeamName() const;
    void setTeamName(const QString &value);

    QString getTeamDescription() const;
    void setTeamDescription(const QString &value);

    QString getBattle() const;

    QVector<Monster *> getMonsters() const;

    Monster* getMonster(int index) const;

private:
    QString battle_m;
    QString teamName_m;
    QString teamDescription_m;
    QVector<Monster *> monsters_m;
};
Q_DECLARE_METATYPE(Team);
Q_DECLARE_METATYPE(Team*);

class Monster : public QObject
{
    Q_OBJECT
public:
    Monster(const QJsonObject &newMonster);
    Monster(const Monster &copyMonster);
    Monster();
    ~Monster();

    friend void Team::addMonster(Monster *monster);
    friend void Team::removeMonster(Monster *monster);

    int getAccuracy() const;
    void setAccuracy(int value);

    int getAttack() const;
    void setAttack(int value);

    bool isAwakened() const;
    //  no setter

    int getCritDamage() const;
    void setCritDamage(int value);

    int getCritRate() const;
    void setCritRate(int value);

    int getDefense() const;
    void setDefense(int value);

    QString getDescription() const;
    void setDescription(const QString &value);

    QString getElement() const;
    //  no setter

    int getHp() const;
    void setHp(int value);

    int getId() const;
    //  no setter

    QString getImagePath() const;
    //  no setter

    int getLevel() const;
    void setLevel(int value);

    QString getName() const;

    int getPriority() const;
    void setPriority(int value);

    int getResistance() const;
    void setResistance(int value);

    int getSpeed() const;
    void setSpeed(int value);

    int getStars() const;
    void setStars(int value);

    QString getUuid() const;
    //  no setter

    QImage getImage() const;
    void setImage(const QImage &value);

    void setName(const QString &value);

private slots:
    void onImageReceived(QNetworkReply *reply);

signals:
    void imageChanged();

private:
    void addTeam(Team *team);
    void removeTeam(Team *team);

    //  Order of JSON attributes
    int     accuracy_m;
    int     attack_m;
    bool    awakened_m;         //
    int     critDamage_m;
    int     critRate_m;
    int     defense_m;
    QString description_m;
    QString element_m;          //
    int     hp_m;
    int     id_m;               //
    QString imagePath_m;        //
    int     level_m;
    QString name_m;
    int     priority_m;
    int     resistance_m;
    int     speed_m;
    int     stars_m;
    QString uuid_m;             //
    //-----------------------------------------

    QImage  image_m;

    QVector<Team *> teams_m;
};
Q_DECLARE_METATYPE(Monster);
Q_DECLARE_METATYPE(Monster*);

class Profile : public QObject
{
    Q_OBJECT
public:
    Profile();

    int monstersSize();
    void addMonster(Monster *mon);
    void removeMonsterAt(int index);
    Monster* getMonster(int index) const;

    int teamsSize();
    void addTeam(Team *team);
    void removeTeamAt(int index);
    Team* getTeam(int index) const;

    QJsonDocument getJson() const;

    QVector<Monster *> getMonsters() const;

private slots:
    void onMonsterImageChanged();

signals:
    void monsterImageChanged(int index);

private:
    QVector<Monster *> monsters_m;
    QVector<Team *> teams_m;
};

#endif // PROFILE_H
