//
//  History.hpp
//  Project 1
//
//  Created by Hender Lin on 4/4/21.
//

#ifndef History_h
#define History_h
#include "globals.h"
#include <stdio.h>

class History
    {
    public:
        History(int nRows, int nCols);
        bool record(int r, int c);
        void display() const;
    private:
        int m_rows;
        int m_cols;
        int m_Grid[MAXROWS][MAXCOLS];
    };

#endif /* History_h */
