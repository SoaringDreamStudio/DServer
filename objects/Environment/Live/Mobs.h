#pragma once
#include "../Live.h"
#include "../../../struct.h"
class Mobs : public Live
{
public:

    Mobs(coordinates* spawn,
                        int ID,
                        int PosX,
                        int PosY);

	~Mobs(void);

	void LoadConfigs();
protected:
    bool Aggressive;
    Rect AgroRange;

};
