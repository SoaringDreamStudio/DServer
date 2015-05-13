#pragma once
#include "../Objects.h"
class Trigger : public Objects
{
public:
    Trigger(Rect Hitbox,
            bool ExistOnMap,
            int ID,
            int PosX,
            int PosY,
            std::string ActiveAnimation,
            std::vector<AnimationInfo> Animations,
            bool Collision,
            bool BulletCollision,
            bool Status,
            int ConnectionID);

	~Trigger(void);
protected:
    bool Status;
    int ConnectionID;

};
