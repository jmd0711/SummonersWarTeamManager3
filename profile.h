#ifndef PROFILE_H
#define PROFILE_H

#include <QObject>
#include <QPixmap>

struct Monster
{
    QString name_m;
    QString imagePath_m;
    QString element_m;
    QString description_m;
    bool awakened_m;
    int id_m;
    int stars_m;
    int level_m;
    int hp_m;
    int attack_m;
    int defense_m;
    int speed_m;
    int critRate_m;
    int critDamage_m;
    int resistance_m;
    int accuracy_m;
    int priority_m;

    int index_m;
    QPixmap image_m;
};

class Profile
{
public:
    Profile();
    ~Profile();

private:
    QVector<Monster> monsters;

};

#endif // PROFILE_H
