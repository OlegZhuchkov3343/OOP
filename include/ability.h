#ifndef ABILITY_H
#define ABILITY_H
#include <random>
#include "gamefield.h"

enum Abilities{DoubleDamage_, Scanner_, Scattershot_};

class Ability {
public:
    Ability() = default;
    virtual void Activate(Coordinate target, GameField& field) = 0;
    virtual std::string name() = 0;
    virtual ~Ability() = default;
};

class DoubleDamage : public Ability {
public:
    void Activate(Coordinate target, GameField& field) override;
    std::string name() override;
};

class Scanner : public Ability {
public:
    void Activate(Coordinate target, GameField& field) override;
    std::string name() override;
};

class Scattershot : public Ability {
public:
    void Activate(Coordinate _target, GameField& field) override;
    std::string name() override;
};
#endif