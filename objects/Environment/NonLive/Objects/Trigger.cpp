#include "Trigger.h"
Trigger::Trigger(Rect passed_Hitbox,
                bool passed_ExistOnMap,
                int passed_ID,
                int passed_PosX,
                int passed_PosY,
                std::string passed_ActiveAnimation,
                std::vector<AnimationInfo> passed_Animations,
                bool passed_Collision,
                bool passed_BulletCollision,
                bool passed_Status,
                int passed_ConnectionID)
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
    Status = passed_Status;
    ConnectionID = passed_ConnectionID;
}

Trigger::~Trigger(void)
{

}
