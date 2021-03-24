#include "profile.h"

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

void Monster::addTeam(Team *team)
{
    teams_m.push_back(team);
}

void Monster::removeTeam(Team *team)
{
    teams_m.erase(std::remove(teams_m.begin(), teams_m.end(), team), teams_m.end());
}

Profile::Profile()
{

}
