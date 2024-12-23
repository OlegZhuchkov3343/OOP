#include "abilitymanager.h"


AbilityManager::AbilityManager() {
    this->gainAbility();
}

void AbilityManager::useAbility(GameField& field, Coordinate target){
    if (this->getAbilityCount() == 0){
        throw NoAbilitiesException("Has no available abilities to use!");
    }
    abilities.front()->Activate(target, field);
    abilities.pop();
}

Ability* AbilityManager::createAbility(Abilities ability) {
    switch (ability) {
        case DoubleDamage_:{
            return new DoubleDamage;
            break;
    }
        case Scanner_:{
            return new Scanner;
            break;
    }
        case Scattershot_:{
            return new Scattershot;
            break;
        }
    }
}

void AbilityManager::gainAbility() {
    std::vector<Abilities> choices = {DoubleDamage_, Scanner_, Scattershot_};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, choices.size() - 1);
    int random_index = dis(gen);
    abilities.push(this->createAbility(choices[random_index]));
    std::cout << "Gained ability: " << this->getAbilityName() << std::endl;
}
    
int AbilityManager::getAbilityCount() const{
    return abilities.size();
}

void AbilityManager::popAbility() {
    abilities.pop();
}

std::string AbilityManager::getAbilityName() const {
    return abilities.front()->name();
}

std::queue<Ability*> AbilityManager::getAll() {
    return this->abilities;
}

