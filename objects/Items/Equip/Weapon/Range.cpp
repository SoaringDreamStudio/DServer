#include "Range.h"
Range::Range(int passed_ID,
                int passed_AD,
                int passed_Range,
                std::string passed_AttackAnimationName,
                int passed_RequireItemID)
    :Weapon(passed_ID,
                passed_AD,
                passed_Range,
                passed_AttackAnimationName)
{
    RequireItemID = passed_RequireItemID;
}

Range::~Range(void)
{

}
