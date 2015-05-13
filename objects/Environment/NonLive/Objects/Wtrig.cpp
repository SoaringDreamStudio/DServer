#include "Wtrig.h"

Wtrig::Wtrig(Rect passed_Hitbox,
                bool passed_ExistOnMap,
                int passed_ID,
                int passed_PosX,
                int passed_PosY,
                std::string passed_ActiveAnimation,
                std::vector<AnimationInfo> passed_Animations,
                bool passed_Collision,
                bool passed_BulletCollision,
                int passed_ConnectionID,
                bool passed_Status
                )
    : Objects(passed_Hitbox,
                passed_ExistOnMap,
                passed_ID,
                passed_PosX,
                passed_PosY,
                passed_ActiveAnimation,
                passed_Animations,
                passed_Collision,
                passed_BulletCollision
                )
{
    ConnectionID = passed_ConnectionID;
    Status = passed_Status;
}

Wtrig::~Wtrig(void)
{

}
