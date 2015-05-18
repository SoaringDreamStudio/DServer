#include "Wtrig.h"

Wtrig::Wtrig(coordinates* passed_spawn,
                int passed_ID,
                int passed_PosX,
                int passed_PosY,
                bool passed_Status,
                int passed_ConnectionID)
    : Objects("Wtrig",
                passed_spawn,
                passed_ID,
                passed_PosX,
                passed_PosY)
{

}

Wtrig::~Wtrig(void)
{

}
