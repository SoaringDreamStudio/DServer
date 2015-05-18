#include "NonLive.h"

NonLive::NonLive(std::string passed_className,
            coordinates* passed_spawn,
            int passed_ID,
            int passed_PosX,
            int passed_PosY)
    :Environment(passed_className,
                passed_spawn,
                passed_ID,
                passed_PosX,
                passed_PosY)

{

}

NonLive::~NonLive(void)
{

}

void  NonLive::LoadConfigs(void)
{

}
