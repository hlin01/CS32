//
//  Game.hpp
//  Project 1
//
//  Created by Hender Lin on 4/4/21.
//

#ifndef Game_h
#define Game_h
#include "City.h"
#include <string>
#include <stdio.h>

class Game
{
  public:
        // Constructor/destructor
    Game(int rows, int cols, int nFlatulans);
    ~Game();

        // Mutators
    void play();
    int decodeDirection(char dir);

  private:
    City* m_city;
};

#endif /* Game_h */
