// Game.cpp

#include "provided.h"
#include "support.h"
using namespace std;

class GameImpl
{
public:
    GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black);
    bool completed(int& winner) const;
    bool takeTurn();
    void play();
    int checkerAt(int c, int r) const;
    
private:
    int m_turn;
    int m_N;
    int lastcolumn;
    Scaffold s;
    Player* redplayer;
    Player* blackplayer;
};

GameImpl::GameImpl(int nColumns, int nLevels, int N, Player* red, Player* black) : s(nColumns, nLevels)
{
    if (N > nColumns && N > nLevels)
    {
        cerr << "N not valid!" << endl;
        exit(1);
    }
    m_turn = RED;
    m_N = N;
    redplayer = red;
    blackplayer = black;
    lastcolumn = 0;
}

bool GameImpl::completed(int& winner) const
{
    int num = 0;
    int turn = oppositeColor(m_turn);
    int lastlevel = 0;
    for (int i = s.levels(); i >= 1; i--)
    {
        if (s.checkerAt(lastcolumn, i) != VACANT)
        {
            //identifies level of last move
            lastlevel = i;
            break;
        }
    }
    //checks for connect N from W to E
    for (int i = -m_N+1; i < m_N; i++)
    {
        if (lastcolumn+i > 0 && lastcolumn+i <= s.cols() && lastlevel > 0 && lastlevel <= s.levels())
        {
            if (s.checkerAt(lastcolumn+i, lastlevel) == turn)
            {
                num++;
                if (num == m_N)
                {
                    winner = turn;
                    return true;
                }
            }
            else
            {
                num = 0;
            }
        }
        else
        {
            num = 0;
        }
    }
    num = 0;
    //checks for connect N from S to N
    for (int i = -m_N+1; i < m_N; i++)
    {
        if (lastcolumn > 0 && lastcolumn <= s.cols() && lastlevel+i > 0 && lastlevel+i <= s.levels())
        {
            if (s.checkerAt(lastcolumn, lastlevel+i) == turn)
            {
                num++;
                if (num == m_N)
                {
                    winner = turn;
                    return true;
                }
            }
            else
            {
                num = 0;
            }
        }
        else
        {
            num = 0;
        }
    }
    num = 0;
    //checks for connect N from SW to NE
    for (int i = -m_N+1; i < m_N; i++)
    {
        if (lastcolumn+i > 0 && lastcolumn+i <= s.cols() && lastlevel+i > 0 && lastlevel+i <= s.levels())
        {
            if (s.checkerAt(lastcolumn+i, lastlevel+i) == turn)
            {
                num++;
                if (num == m_N)
                {
                    winner = turn;
                    return true;
                }
            }
            else
            {
                num = 0;
            }
        }
        else
        {
            num = 0;
        }
    }
    num = 0;
    //checks for connect N from NW to SE
    for (int i = -m_N+1; i < m_N; i++)
    {
        if (lastcolumn+i > 0 && lastcolumn+i <= s.cols() && lastlevel-i > 0 && lastlevel-i <= s.levels())
        {
            if (s.checkerAt(lastcolumn+i, lastlevel-i) == turn)
            {
                num++;
                if (num == m_N)
                {
                    winner = turn;
                    return true;
                }
            }
            else
            {
                num = 0;
            }
        }
        else
        {
            num = 0;
        }
    }
    num = 0;
    //if no moves remain return tie game
    if (s.numberEmpty() == 0)
    {
        winner = TIE_GAME;
        return true;
    }
    return false;
}

bool GameImpl::takeTurn()
{
    int move;
    //identifies whose turn it is and makes move
    if (m_turn == RED)
    {
        move = redplayer->chooseMove(s, m_N, RED);
        s.makeMove(move, RED);
        lastcolumn = move;
        m_turn = BLACK;
        return true;
    }
    else
    {
        move = blackplayer->chooseMove(s, m_N, BLACK);
        s.makeMove(move, BLACK);
        lastcolumn = move;
        m_turn = RED;
        return true;
    }
    return false;
}

void GameImpl::play()
{
    int winner;
    //while winner has not been decided, take turns and display to screen
    do
    {
        takeTurn();
        s.display();
    }
    while (completed(winner) == false);
    //print who wins
    if (winner == RED)
    {
        cout << "RED WON!" << endl;
    }
    else if (winner == BLACK)
    {
        cout << "BLACK WON!" << endl;
    }
    else if (winner == TIE_GAME)
    {
        cout << "TIE GAME!" << endl;
    }
}

int GameImpl::checkerAt(int c, int r) const
{
    if (s.checkerAt(c, r) == 0)
    {
        return RED;
    }
    if (s.checkerAt(c, r) == 1)
    {
        return BLACK;
    }
    if (s.checkerAt(c, r) == -1)
    {
        return VACANT;
    }
    return -1;
}

//******************** Game functions *******************************

//  These functions simply delegate to GameImpl's functions.
//  You probably don't want to change any of this code.

Game::Game(int nColumns, int nLevels, int N, Player* red, Player* black)
{
    m_impl = new GameImpl(nColumns, nLevels, N, red, black);
}
 
Game::~Game()
{
    delete m_impl;
}
 
bool Game::completed(int& winner) const
{
    return m_impl->completed(winner);
}

bool Game::takeTurn()
{
    return m_impl->takeTurn();
}

void Game::play()
{
    m_impl->play();
}
 
int Game::checkerAt(int c, int r) const
{
    return m_impl->checkerAt(c, r);
}
