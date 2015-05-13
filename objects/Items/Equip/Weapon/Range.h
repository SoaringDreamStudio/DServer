#pragma once
#include "../Weapon.h"
class Range : public Weapon
{
public:
    Range(int ID,
            int AD,
            int Range,
            std::string AttackAnimationName,
            int RequireItemID);

	~Range(void);
protected:
    int RequireItemID;

};
