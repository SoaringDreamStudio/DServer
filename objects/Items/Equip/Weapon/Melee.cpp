#include "Melee.h"
Melee::Melee(int passed_ID,
            int passed_AD,
            int passed_Range,
            std::string passed_AttackAnimationName,
            Rect passed_hitBox)

    : Weapon(passed_ID,
                passed_AD,
                passed_Range,
                passed_AttackAnimationName)
{
    hitBox = passed_hitBox;
}

Melee::~Melee(void)
{

}
