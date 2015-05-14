#include "Characters.h"
Characters::Characters(Rect passed_Hitbox,
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
                        int passed_AttackAnimationTime,
                        std::string passed_NickName,
                        std::vector<Items> passed_Inventory,
                        int passed_WSLOT,
                        int passed_ASLOT,
                        int passed_Hunger
                        )
        : Live(passed_Hitbox,
                passed_ExistOnMap,
                passed_ID,
                passed_PosX,
                passed_PosY,
                passed_ActiveAnimation,
                passed_Animations,
                passed_fpX,
                passed_fpY,
                passed_HP,
                passed_MS,
                passed_Range,
                passed_AttackDmg,
                passed_Defense,
                passed_AttackCDTime,
                passed_AttackAnimationTime)
{
    NickName = passed_NickName;
    Inventory = passed_Inventory;
    WSLOT = passed_WSLOT;
    ASLOT = passed_ASLOT;
    Hunger = passed_Hunger;
}
Characters::Characters(int passed_ID,
                int passed_PosX,
                int passed_PosY,
                std::string passed_NickName
                )
        : Live(passed_ID,
                passed_PosX,
                passed_PosY)
{
    NickName = passed_NickName;

}

Characters::~Characters(void)
{

}
