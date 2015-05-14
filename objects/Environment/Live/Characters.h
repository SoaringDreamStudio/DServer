#pragma once
#include "../Live.h"
#include "../../Items.h"
class Characters : public Live
{
public:
    Characters(Rect Hitbox,
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
                std::string NickName,
                std::vector<Items> Inventory,
                int WSLOT,
                int ASLOT,
                int Hunger
                );
    Characters(int ID,
                int PosX,
                int PosY,
                std::string NickName
                );

	~Characters(void);
protected:
    std::string NickName;
    std::vector<Items> Inventory;
    int WSLOT;
    int ASLOT;
    int Hunger;

};
