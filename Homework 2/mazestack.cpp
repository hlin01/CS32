//
//  main.cpp
//  Homework 2
//
//  Created by Hender Lin on 4/24/21.
//

#include <iostream>
#include <stack>
using namespace std;

class Coord
{
    public:
        Coord(int r, int c) : m_row(r), m_col(c) {}
        int r() const { return m_row; }
        int c() const { return m_col; }
    private:
        int m_row;
        int m_col;
};

bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
    stack<Coord> coordStack;
    coordStack.push(Coord(sr,sc));
    maze[sr][sc] = '+';
    while (!coordStack.empty())
    {
        Coord current = coordStack.top();
        coordStack.pop();
        int r = current.r();
        int c = current.c();
        if (r == er && c == ec)
        {
            return true;
        }
        if (maze[r+1][c] == '.')
        {
            coordStack.push(Coord(r+1,c));
            maze[r+1][c] = '+';
        }
        if (maze[r][c-1] == '.')
        {
            coordStack.push(Coord(r,c-1));
            maze[r][c-1] = '+';
        }
        if (maze[r-1][c] == '.')
        {
            coordStack.push(Coord(r-1,c));
            maze[r-1][c] = '+';
        }
        if (maze[r][c+1] == '.')
        {
            coordStack.push(Coord(r,c+1));
            maze[r][c+1] = '+';
        }
    }
    return false;
}
