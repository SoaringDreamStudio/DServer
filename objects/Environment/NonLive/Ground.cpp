#include "Ground.h"

Ground::Ground(Rect passed_Hitbox,
                bool passed_ExistOnMap,
                int passed_ID,
                int passed_PosX,
                int passed_PosY,
                std::string passed_ActiveAnimation,
                std::vector<AnimationInfo> passed_Animations)
    : NonLive( passed_Hitbox,
            passed_ExistOnMap,
            passed_ID,
            passed_PosX,
            passed_PosY,
            passed_ActiveAnimation,
            passed_Animations)
{

}

Ground::~Ground(void)
{

}
