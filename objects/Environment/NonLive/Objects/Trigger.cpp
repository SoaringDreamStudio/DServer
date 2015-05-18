#include "Trigger.h"

Trigger::Trigger(coordinates* passed_spawn,
                int passed_ID,
                int passed_PosX,
                int passed_PosY,
                bool passed_Status,
                int passed_ConnectionID)
        : Objects("Trigger",
                passed_spawn,
                passed_ID,
                passed_PosX,
                passed_PosY)
{

}

Trigger::~Trigger(void)
{

}

