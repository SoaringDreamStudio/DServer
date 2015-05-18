#include "Characters.h"

Characters::Characters(coordinates* passed_spawn,
                        int passed_ID,
                        int passed_PosX,
                        int passed_PosY,
                        std::string passed_NickName
                        )
        : Live("Characters",
                passed_spawn,
                passed_ID,
                passed_PosX,
                passed_PosY)
{
    NickName = passed_NickName;
}

Characters::~Characters(void)
{

}
