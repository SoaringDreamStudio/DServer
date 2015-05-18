#pragma once
#include "../Objects.h"
class Normal : public Objects
{
public:

    Normal(coordinates* spawn,
            int ID,
            int PosX,
            int PosY);


	~Normal(void);

	void LoadConfigs();
protected:
    bool PickUpAble;

};
