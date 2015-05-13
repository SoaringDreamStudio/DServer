#pragma once
#include "../Equip.h"
class Armor : public Equip
{
public:
    Armor(int ID,
          int def);

	~Armor(void);
protected:
    int def;
};
