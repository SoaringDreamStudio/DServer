#pragma once
#include "../NonLive.h"
class Ground : public NonLive
{
public:

    Ground(coordinates* spawn,
                int ID,
                int PosX,
                int PosY);

	~Ground(void);

};
