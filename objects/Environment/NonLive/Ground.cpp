#include "Ground.h"

Ground::Ground(coordinates* passed_spawn,
                        int passed_ID,
                        int passed_PosX,
                        int passed_PosY
                        )
        : NonLive("Ground",
                passed_spawn,
                passed_ID,
                passed_PosX,
                passed_PosY)
{

}

Ground::~Ground(void)
{

}
