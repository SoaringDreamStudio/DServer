#pragma once
#include "../Live.h"
#include "../../../struct.h"
class Mobs : public Live
{
public:
    Mobs(Rect Hitbox,
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
    int AttackAnimationTime,
    bool Aggressive,
    Rect AgroRange
    );

	~Mobs(void);
protected:
    bool Aggressive;
    Rect AgroRange;

};
