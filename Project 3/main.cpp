// main.cpp

#include "provided.h"
#include <string>
#include <iostream>
using namespace std;

int main()
    {
        SmartPlayer bp1("Bart");
        SmartPlayer bp2("Homer");
        Game g(5, 4, 4, &bp1, &bp2);
        g.play();
    }
