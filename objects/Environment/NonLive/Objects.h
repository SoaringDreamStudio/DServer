#pragma once
#include "../NonLive.h"
class Objects : public NonLive
{
public:
    Objects(Rect Hitbox,
            bool ExistOnMap,
            int ID,
            int PosX,
            int PosY,
            std::string ActiveAnimation,
            std::vector<AnimationInfo> Animations,
            bool Collision,
            bool BulletCollision
            );

	~Objects(void);
protected:
    bool Collision;
    bool BulletCollision;
};
