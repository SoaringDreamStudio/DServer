#include "NonLive.h"

NonLive::NonLive(Rect passed_Hitbox,
                bool passed_ExistOnMap,
                int passed_ID,
                int passed_PosX,
                int passed_PosY,
                std::string passed_ActiveAnimation,
                std::vector<AnimationInfo> passed_Animations)

    : Environment(passed_Hitbox,
                    passed_ExistOnMap,
                    passed_ID,
                    passed_PosX,
                    passed_PosY,
                    passed_ActiveAnimation,
                    passed_Animations)
{

}

NonLive::~NonLive(void)
{

}
