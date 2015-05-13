#include "Normal.h"

Normal::Normal(Rect passed_Hitbox,
            bool passed_ExistOnMap,
            int passed_ID,
            int passed_PosX,
            int passed_PosY,
            std::string passed_ActiveAnimation,
            std::vector<AnimationInfo> passed_Animations,
            bool passed_Collision,
            bool passed_BulletCollision,
            bool passed_PickUpAble)
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
    PickUpAble = passed_PickUpAble;
}

Normal::~Normal(void)
{

}
