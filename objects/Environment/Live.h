#pragma once
#include "../Environment.h"
class Live : public Environment
{
public:
    Live(Rect Hitbox,
    bool ExistOnMap,
    int ID,
    int PosX,
    int PosY,
    std::string ActiveAnimation,
    std::vector<AnimationInfo> Animations,
    int fpX,
    int fpY,
    int HP,
    int MS,
    int Range,
    int AttackDmg,
    int Defense,
    int AttackCDTime,
    int AttackAnimationTime);

	~Live(void);
protected:
    int fpX;
    int fpY;
    int HP;
    int MS;
    int Range;
    int AttackDmg;
    int Defense;
    int AttackCDTime;
    int AttackAnimationTime;
};
