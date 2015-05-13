#include "Live.h"

Live::Live(Rect passed_Hitbox,
            bool passed_ExistOnMap,
            int passed_ID,
            int passed_PosX,
            int passed_PosY,
            std::string passed_ActiveAnimation,
            std::vector<AnimationInfo> passed_Animations,
            int passed_fpX,
            int passed_fpY,
            int passed_HP,
            int passed_MS,
            int passed_Range,
            int passed_AttackDmg,
            int passed_Defense,
            int passed_AttackCDTime,
            int passed_AttackAnimationTime)

        : Environment(passed_Hitbox,
                    passed_ExistOnMap,
                    passed_ID,
                    passed_PosX,
                    passed_PosY,
                    passed_ActiveAnimation,
                    passed_Animations)
{
    fpX = passed_fpX;
    fpY = passed_fpY;
    HP = passed_HP;
    MS = passed_MS;
    Range = passed_Range;
    AttackDmg = passed_AttackDmg;
    Defense = passed_Defense;
    AttackCDTime = passed_AttackCDTime;
    AttackAnimationTime = passed_AttackAnimationTime;
}

Live::~Live(void)
{

}

