#pragma once
#include "../Live.h"
#include "../../Items.h"
class Characters : public Live
{
public:

    Characters(coordinates* spawn,
                int ID,
                int PosX,
                int PosY,
                std::string NickName
                );

	~Characters(void);

	std::string getNickName() {return NickName;}

protected:
    std::string NickName;
    std::vector<Items> Inventory;
    int WSLOT;
    int ASLOT;
    int Hunger;

};
