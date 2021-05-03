//
//  maze.cpp
//  Homework 3
//
//  Created by Hender Lin on 5/2/21.
//

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
    if (sr == er && sc == ec)
    {
        return true;
    }
    maze[sr][sc] = '+';
    if (maze[sr+1][sc] == '.')
    {
        if (pathExists(maze, sr+1, sc, er, ec))
        {
            return true;
        }
    }
    if (maze[sr][sc-1] == '.')
    {
        if (pathExists(maze, sr, sc-1, er, ec))
        {
            return true;
        }
    }
    if (maze[sr-1][sc] == '.')
    {
        if (pathExists(maze, sr-1, sc, er, ec))
        {
            return true;
        }
    }
    if (maze[sr][sc+1] == '.')
    {
        if (pathExists(maze, sr, sc+1, er, ec))
        {
            return true;
        }
    }
    return false;
}
