#include "Weapon.h"

Weapon::Weapon(int passed_ID,
                int passed_AD,
                int passed_Range,
                std::string passed_AttackAnimationName)
    : Equip(passed_ID)
{
    AD = passed_AD;
    Range = passed_Range;
    AttackAnimationName = passed_AttackAnimationName;

}

Weapon::~Weapon(void)
{

}
