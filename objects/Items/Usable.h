#pragma once
#include "../Items.h"
class Usable : public Items
{
public:
    Usable(int ID,
            int MaxCount,
            bool Limited,
            int Count);

	~Usable(void);
protected:
    int MaxCount;
    bool Limited;
    int Count;

};
