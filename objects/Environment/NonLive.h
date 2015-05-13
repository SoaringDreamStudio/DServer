#pragma once
#include "../Environment.h"
class NonLive : public Environment
{
public:
    NonLive(Rect Hitbox,
            bool ExistOnMap,
            int ID,
            int PosX,
            int PosY,
            std::string ActiveAnimation,
            std::vector<AnimationInfo> Animations);

	~NonLive(void);

};
