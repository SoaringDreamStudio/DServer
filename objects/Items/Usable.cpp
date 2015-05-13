#include "Usable.h"
Usable::Usable(int passed_ID,
                int passed_MaxCount,
                bool passed_Limited,
                int passed_Count)
    : Items(passed_ID)
{
    MaxCount = passed_MaxCount;
    Limited = passed_Limited;
    Count = passed_Count;

}

Usable::~Usable(void)
{

}
