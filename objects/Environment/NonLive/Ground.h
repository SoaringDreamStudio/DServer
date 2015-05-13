#pragma once
#include "../NonLive.h"
class Ground : public NonLive
{
public:
    Ground(Rect Hitbox,
            bool ExistOnMap,
            int ID,
            int PosX,
            int PosY,
            std::string ActiveAnimation,
            std::vector<AnimationInfo> Animations);

	~Ground(void);


};
