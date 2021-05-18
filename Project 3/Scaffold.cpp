// Scaffold.cpp

#include "provided.h"
#include "support.h"
using namespace std;

class ScaffoldImpl
{
public:
    ScaffoldImpl(int nColumns, int nLevels);
    int cols() const;
    int levels() const;
    int numberEmpty() const;
    int checkerAt(int column, int level) const;
    void display() const;
    bool makeMove(int column, int color);
    int undoMove();
    
private:
    int m_cols;
    int m_levels;
    int m_num;
    vector<vector<int>> grid;
    stack<vector<int>> moves;
};

ScaffoldImpl::ScaffoldImpl(int nColumns, int nLevels)
{
    if (nColumns <= 0 || nLevels <= 0)
    {
        cerr << "Non-positive Dimension!" << endl;
        exit(1);
        
    }
    m_cols = nColumns;
    m_levels = nLevels;
    m_num = 0;
    grid.resize(nLevels);
    //initialize grid to set size
    for (int i = 0; i < nLevels; i++)
    {
        grid[i].resize(nColumns);
        for (int j = 0; j < nColumns; j++)
        {
            grid[i][j] = VACANT;
        }
    }
}

int ScaffoldImpl::cols() const
{
    return m_cols;
}

int ScaffoldImpl::levels() const
{
    return m_levels;
}

int ScaffoldImpl::numberEmpty() const
{
    return cols()*levels()-m_num;
}

int ScaffoldImpl::checkerAt(int column, int level) const
{
    if (grid[levels()-level][column-1] == 0)
    {
        return RED;
    }
    if (grid[levels()-level][column-1] == 1)
    {
        return BLACK;
    }
    if (grid[levels()-level][column-1] == -1)
    {
        return VACANT;
    }
    return -1;
}

void ScaffoldImpl::display() const
{
    for (int i = 0; i < m_levels; i++)
    {
        for (int j = 0; j < m_cols; j++)
        {
            cout << "|";
            if (grid[i][j] == RED)
            {
                cout << "R";
            }
            else if (grid[i][j] == BLACK)
            {
                cout << "B";
            }
            else
            {
                cout << " ";
            }
        }
            cout << "|" << endl;
    }
    int k = 0;
    for (int i = 0; i != cols()*2+1; i++)
    {
        switch (k)
        {
            case 0:
                cout << "+";
                k = 1;
                break;
            case 1:
                cout << "-";
                k = 0;
                break;
            default:
                break;
        }
    }
    cout << endl;
}

bool ScaffoldImpl::makeMove(int column, int color)
{
    if (column > 0 && column <= m_cols && (color == RED || color == BLACK))
    {
        for (int i = m_levels-1; i >= 0; i--)
        {
            if (grid[i][column-1] == VACANT)
            {
                //if move is valid: make move, increment number of checkers, add move to stack
                grid[i][column-1] = color;
                m_num++;
                moves.push({i,column-1});
                return true;
            }
        }
        return false;
    }
    return false;
}

int ScaffoldImpl::undoMove()
{
    if (numberEmpty() == cols()*levels())
    {
        return 0;
    }
    vector<int> pastmove;
    pastmove = moves.top();
    int l = pastmove[0];
    int c = pastmove[1];
    //remove last move from stack if possible and set space to VACANT
    moves.pop();
    grid[l][c] = VACANT;
    m_num--;
    return l;
}

//******************** Scaffold functions *******************************

//  These functions simply delegate to ScaffoldImpl's functions.
//  You probably don't want to change any of this code.

Scaffold::Scaffold(int nColumns, int nLevels)
{
    m_impl = new ScaffoldImpl(nColumns, nLevels);
}
 
Scaffold::~Scaffold()
{
    delete m_impl;
}
 
Scaffold::Scaffold(const Scaffold& other)
{
    m_impl = new ScaffoldImpl(*other.m_impl);
}
 
Scaffold& Scaffold::operator=(const Scaffold& rhs)
{
    if (this != &rhs)
    {
        Scaffold temp(rhs);
        swap(m_impl, temp.m_impl);
    }
    return *this;
}
 
int Scaffold::cols() const
{
    return m_impl->cols();
}

int Scaffold::levels() const
{
    return m_impl->levels();
}

int Scaffold::numberEmpty() const
{
    return m_impl->numberEmpty();
}

int Scaffold::checkerAt(int column, int level) const
{
    return m_impl->checkerAt(column, level);
}
 
void Scaffold::display() const
{
    m_impl->display();
}
 
bool Scaffold::makeMove(int column, int color)
{
    return m_impl->makeMove(column, color);
}
 
int Scaffold::undoMove()
{
    return m_impl->undoMove();
}
