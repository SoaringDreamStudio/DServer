#include "Environment.h"
Environment::Environment(Rect passed_Hitbox,
    bool passed_ExistOnMap,
    int passed_ID,
    int passed_PosX,
    int passed_PosY,
    std::string passed_ActiveAnimation,
    std::vector<AnimationInfo> passed_Animations)
{
    Hitbox = passed_Hitbox;
    ExistOnMap = passed_ExistOnMap;
    ID = passed_ID;
    PosX = passed_PosX;
    PosY = passed_PosY;
    ActiveAnimation = passed_ActiveAnimation;
    Animations = passed_Animations;
}

Environment::~Environment(void)
{

}
