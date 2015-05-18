#pragma once
#include "../NonLive.h"
class Objects : public NonLive
{
public:

    Objects(std::string className,
            coordinates* spawn,
            int ID,
            int PosX,
            int PosY);

	~Objects(void);

	void LoadConfigs();
protected:
    bool Collision;
    bool BulletCollision;
};
