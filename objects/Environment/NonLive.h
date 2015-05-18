#pragma once
#include "../Environment.h"
class NonLive : public Environment
{
public:

    NonLive(std::string className,
            coordinates* spawn,
            int ID,
            int PosX,
            int PosY);

	~NonLive(void);

	void LoadConfigs();

};
