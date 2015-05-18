#pragma once
#include "struct.h"

bool allTrue(bool x[], int Size)
{
    for(int i = 0; i < Size; i++)
    {
        if(x[i] == false)
            return false;
    }
    return true;
}
