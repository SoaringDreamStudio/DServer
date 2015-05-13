#pragma once
#include "../Objects.h"
class Wtrig : public Objects
{
public:
    Wtrig(Rect Hitbox,
    bool ExistOnMap,
    int ID,
    int PosX,
    int PosY,
    std::string ActiveAnimation,
    std::vector<AnimationInfo> Animations,
    bool Collision,
    bool BulletCollision,
    int ConnectionID,
    bool Status
    );

	~Wtrig(void);

protected:
    int ConnectionID;
    bool Status;

};
