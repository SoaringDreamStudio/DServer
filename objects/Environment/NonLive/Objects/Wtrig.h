#pragma once
#include "../Objects.h"
class Wtrig : public Objects
{
public:

    Wtrig(coordinates* spawn,
                int ID,
                int PosX,
                int PosY,
                bool Status,
                int ConnectionID);

	~Wtrig(void);


protected:
    int ConnectionID;
    bool Status;

};
