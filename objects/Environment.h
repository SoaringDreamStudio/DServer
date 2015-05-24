#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include "../struct.h"
class Environment
{
public:
	Environment(std::string className,
                coordinates* spawn,
                int ID,
                int PosX,
                int PosY);

	~Environment(void);

	void LoadConfigs();
	void changeXY(int X, int Y);
	int getID() {return ID;}
	int getX() {return PosX;}
	int getY() {return PosY;}

    void setActiveAnimation(std::string passed_AA) { ActiveAnimation = passed_AA;}
    std::string getActiveAnimation() {return ActiveAnimation;}

protected:
    bool ExistOnMap;
    int ID;
    int PosX;
    int PosY;
    std::string ActiveAnimation;
    std::vector<std::string> Animations;

    coordinates* spawn;

    std::string className;

    Rect hitbox;

    Rect rect;

};
