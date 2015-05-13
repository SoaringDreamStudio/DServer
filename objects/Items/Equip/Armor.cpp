#include "Armor.h"

Armor::Armor(int passed_ID,
          int passed_def)

      :Equip(passed_ID)
{
    def = passed_def;
}

Armor::~Armor(void)
{

}
