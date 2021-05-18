//
//  support.h
//  Project 3
//
//  Created by Hender Lin on 5/15/21.
//

#ifndef support_h
#define support_h

#include <stdio.h>
#include "provided.h"
#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <cstdlib>
#include <algorithm>
#include <ctime>

//returns the opposite color of input
inline int oppositeColor(int color)
{
    int oppcol;
    if (color == RED)
    {
        oppcol = BLACK;
    }
    else
    {
        oppcol = RED;
    }
    return oppcol;
}

#endif /* support_h */
