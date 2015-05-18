#pragma once
#include "../Objects.h"
class Trigger : public Objects
{
public:
    Trigger(coordinates* spawn,
                int ID,
                int PosX,
                int PosY,
                bool Status,
                int ConnectionID);

	~Trigger(void);

protected:
    bool Status;
    int ConnectionID;

};
