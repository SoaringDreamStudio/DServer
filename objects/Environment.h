#pragma once
#include <string>
#include <vector>
#include "../struct.h"
class Environment
{
public:
	Environment(Rect Hitbox,
                bool ExistOnMap,
                int ID,
                int PosX,
                int PosY,
                std::string ActiveAnimation,
                std::vector<AnimationInfo> Animations);
	Environment(int ID,
                int PosX,
                int PosY);

	~Environment(void);

protected:

    Rect Hitbox;
    bool ExistOnMap;
    int ID;
    int PosX;
    int PosY;
    //Sprite(SDL_Sprite)
    std::string ActiveAnimation;
    std::vector<AnimationInfo> Animations;

};
