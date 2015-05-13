#pragma once
#include "../Objects.h"
class Normal : public Objects
{
public:
    Normal(Rect Hitbox,
            bool ExistOnMap,
            int ID,
            int PosX,
            int PosY,
            std::string ActiveAnimation,
            std::vector<AnimationInfo> Animations,
            bool Collision,
            bool BulletCollision,
            bool PickUpAble);

	~Normal(void);
protected:
    bool PickUpAble;

};
