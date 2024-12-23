#ifndef ABILITY_MANAGER_H
#define ABILITY_MANAGER_H
#include <queue>
#include <random>
#include <string>
#include "ability.h"
#include "exceptions.h"


class AbilityManager {
private:
    std::queue<Ability*> abilities;
public:
    AbilityManager();
    void useAbility(GameField& field, Coordinate target = {-1,-1});
    void gainAbility();
    int getAbilityCount() const;
    void popAbility();
    Ability* createAbility(Abilities ability);
    std::string getAbilityName() const;
};
#endif