#pragma once
#include "../Environment.h"
class Live : public Environment
{
public:
    Live(std::string className,
            coordinates* spawn,
            int ID,
            int PosX,
            int PosY);

	~Live(void);

	void LoadConfigs();

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
