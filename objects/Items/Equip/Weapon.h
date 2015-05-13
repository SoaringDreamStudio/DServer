#pragma once
#include <string>
#include "../Equip.h"
class Weapon : public Equip
{
public:
    Weapon(int ID,
            int AD,
            int Range,
            std::string AttackAnimationName);

	~Weapon(void);
protected:
    int AD;
    int Range;
    std::string AttackAnimationName;

};
