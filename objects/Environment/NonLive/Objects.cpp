#include "Objects.h"

Objects::Objects(Rect passed_Hitbox,
            bool passed_ExistOnMap,
            int passed_ID,
            int passed_PosX,
            int passed_PosY,
            std::string passed_ActiveAnimation,
            std::vector<AnimationInfo> passed_Animations,
            bool passed_Collision,
            bool passed_BulletCollision
            )
        : NonLive( passed_Hitbox,
            passed_ExistOnMap,
            passed_ID,
            passed_PosX,
            passed_PosY,
            passed_ActiveAnimation,
            passed_Animations)
{
    Collision = passed_Collision;
    BulletCollision = passed_BulletCollision;
}

Objects::~Objects(void)
{

}
