//
//  History.cpp
//  Project 1
//
//  Created by Hender Lin on 4/4/21.
//

#include "History.h"
#include "City.h"
#include "globals.h"
#include <iostream>
using namespace std;

History::History(int nRows, int nCols)
{
    m_rows = nRows;
    m_cols = nCols;

    for (int r = 0; r < nRows; r++)
    {
        for (int c = 0; c < nCols; c++)
        {
            m_Grid[r][c] = 0;
        }
//        initialize the elements in the array to 0
    }
}

bool History::record(int r, int c)
{
//    if out of range, return false
    if (r < 0  ||  c < 0  ||  r >= MAXROWS  ||  c >= MAXCOLS)
    {
        return false;
    }
    else
    {
        m_Grid[r][c]++;
        return true;
    }
}

void History::display() const
{
    char displayHistoryGrid[MAXROWS][MAXCOLS];
    clearScreen();

    for (int r = 0; r < m_rows; r++)
    {
        for (int c = 0; c < m_cols; c++)
        {
            if (m_Grid[r][c] == 0)
            {
                displayHistoryGrid[r][c] = '.';
            }
            else if (m_Grid[r][c] >= 1 && m_Grid[r][c] < 26)
            {
                displayHistoryGrid[r][c] = 'A' + (m_Grid[r][c]-1);
            }
            else if (m_Grid[r][c] >= 26)
            {
                displayHistoryGrid[r][c] = 'Z';
            }
        }
    }

    for (int r = 0; r < m_rows; r++)
    {
        for (int c = 0; c < m_cols; c++)
        {
            cout << displayHistoryGrid[r][c];
        }
        cout << endl;
    }
    cout << endl;
}
