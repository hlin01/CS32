// Player.cpp

#include "provided.h"
#include "support.h"
using namespace std;

class HumanPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
};

class BadPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
};

class SmartPlayerImpl
{
  public:
    int chooseMove(const Scaffold& s, int N, int color);
};

int HumanPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    if (N <= 0 || (color != RED && color != BLACK))
    {
        exit(1);
    }
    int move;
    int open = 0;
    do
    {
        //enter move after prompt, loops if not valid
        cout << "Enter a move: ";
        cin >> move;
        for (int i = s.levels(); i > 0; i--)
        {
            if (s.checkerAt(move, i) == VACANT)
            {
                open = 1;
                break;
            }
        }
    }
    while (move <= 0 || move > s.cols() || open == 0);
    return move;
}

int BadPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    if (N <= 0 || (color != RED && color != BLACK))
    {
        exit(1);
    }
    int move;
    int open = 0;
    //set seed for rand() function
    srand(unsigned(time(NULL)));
    do
    {
        //pick random move between 1 and # of columns, loops until valid
        move = (rand() % s.cols()) + 1;
        for (int i = s.levels(); i > 0; i--)
        {
            if (s.checkerAt(move, i) == VACANT)
            {
                open = 1;
                break;
            }
        }
    }
    while (move <= 0 || move > s.cols() || open == 0);
    return move;
}

//evaluates board state (rating function)
int evaluate(const Scaffold& s, int N, int color, int lastcolumn)
{
    int n1 = 0;
    int n2 = 0;
    int lastlevel = 0;
    for (int i = s.levels(); i >= 1; i--)
    {
        if (s.checkerAt(lastcolumn, i) != VACANT)
        {
            //identifies which level last move was on
            lastlevel = i;
            break;
        }
    }
    //checks for connect N from W to E and sets score if possible
    for (int i = -N+1; i < N; i++)
    {
        if (lastcolumn+i > 0 && lastcolumn+i <= s.cols() && lastlevel > 0 && lastlevel <= s.levels())
        {
            if (s.checkerAt(lastcolumn+i, lastlevel) == color)
            {
                n1++;
                n2 = 0;
                if (n1 == N)
                {
                    return (1000+s.numberEmpty());
                }
            }
            else if (s.checkerAt(lastcolumn+i, lastlevel) == oppositeColor(color))
            {
                n2++;
                n1 = 0;
                if (n2 == N)
                {
                    return -(1000+s.numberEmpty());
                }
            }
            else
            {
                n1 = 0;
                n2 = 0;
            }
        }
        else
        {
            n1 = 0;
            n2 = 0;
        }
    }
    n1 = 0;
    n2 = 0;
    //checks for connect N from S to N and sets score if possible
    for (int i = -N+1; i < N; i++)
    {
        if (lastcolumn > 0 && lastcolumn <= s.cols() && lastlevel+i > 0 && lastlevel+i <= s.levels())
        {
            if (s.checkerAt(lastcolumn, lastlevel+i) == color)
            {
                n1++;
                n2 = 0;
                if (n1 == N)
                {
                    return (1000+s.numberEmpty());
                }
            }
            else if (s.checkerAt(lastcolumn, lastlevel+i) == oppositeColor(color))
            {
                n2++;
                n1 = 0;
                if (n2 == N)
                {
                    return -(1000+s.numberEmpty());
                }
            }
            else
            {
                n1 = 0;
                n2 = 0;
            }
        }
        else
        {
            n1 = 0;
            n2 = 0;
        }
    }
    n1 = 0;
    n2 = 0;
    //checks for connect N from SW to NE and sets score if possible
    for (int i = -N+1; i < N; i++)
    {
        if (lastcolumn+i > 0 && lastcolumn+i <= s.cols() && lastlevel+i > 0 && lastlevel+i <= s.levels())
        {
            if (s.checkerAt(lastcolumn+i, lastlevel+i) == color)
            {
                n1++;
                n2 = 0;
                if (n1 == N)
                {
                    return (1000+s.numberEmpty());
                }
            }
            else if (s.checkerAt(lastcolumn+i, lastlevel+i) == oppositeColor(color))
            {
                n2++;
                n1 = 0;
                if (n2 == N)
                {
                    return -(1000+s.numberEmpty());
                }
            }
            else
            {
                n1 = 0;
                n2 = 0;
            }
        }
        else
        {
            n1 = 0;
            n2 = 0;
        }
    }
    n1 = 0;
    n2 = 0;
    //checks for connect N from NW to SE and sets score if possible
    for (int i = -N+1; i < N; i++)
    {
        if (lastcolumn+i > 0 && lastcolumn+i <= s.cols() && lastlevel-i > 0 && lastlevel-i <= s.levels())
        {
            if (s.checkerAt(lastcolumn+i, lastlevel-i) == color)
            {
                n1++;
                n2 = 0;
                if (n1 == N)
                {
                    return (1000+s.numberEmpty());
                }
            }
            else if (s.checkerAt(lastcolumn+i, lastlevel-i) == oppositeColor(color))
            {
                n2++;
                n1 = 0;
                if (n2 == N)
                {
                    return -(1000+s.numberEmpty());
                }
            }
            else
            {
                n1 = 0;
                n2 = 0;
            }
        }
        else
        {
            n1 = 0;
            n2 = 0;
        }
    }
    n1 = 0;
    n2 = 0;
    //if no moves left return 0 for tie
    if (s.numberEmpty() == 0)
    {
        return 0;
    }
    //return -10000 indicating game not over
    return -10000;
}

//minimax implementation to determine optimal move
vector<int> determineBestMove(AlarmClock& ac, Scaffold& s, int N, int color, int mod)
{
    bool valid;
    vector<int> rating;
    vector<int> eval;
    map<int,int> moves;
    map<int,int>::iterator it;
    int best;
    int turn;
    int stop = false;
    //identifies whose turn it is throughout recursion
    if (mod % 2 == 0)
    {
        turn = color;
    }
    else
    {
        turn = oppositeColor(color);
    }
    //defaults first move to center of board
    if (s.numberEmpty() == s.cols()*s.levels())
    {
        return {0,s.cols()/2};
    }
    for (int i = 1; i <= s.cols(); i++)
    {
        valid = s.makeMove(i, color);
        if (valid == true)
        {
            //limits move to 10 seconds
            if (ac.timedOut() == false)
            {
                //if move can be made evaluate board or traverse down tree
                eval = {evaluate(s, N, turn, i),i};
                if (eval[0] == -10000)
                {
                    eval = determineBestMove(ac, s, N, oppositeColor(color), mod+1);
                }
            }
            else
            {
                eval = {0,i};
                stop = true;
            }
            //add score to vector and corresponding move to map, undo the move
            rating.push_back(eval[0]);
            moves[eval[0]] = i;
            s.undoMove();
            if (stop == true)
            {
                cerr << "Timed Out!" << endl;
                break;
            }
        }
    }
    //min or max from vector depending on the turn
    if (turn == color)
    {
        best = *max_element(rating.begin(), rating.end());
    }
    else
    {
        best = *min_element(rating.begin(), rating.end());
    }
    //find corresponding move in map and return both values in vector
    it = moves.find(best);
    return {best, it->second};
}

int SmartPlayerImpl::chooseMove(const Scaffold& s, int N, int color)
{
    if (N <= 0 || (color != RED && color != BLACK))
    {
        exit(1);
    }
    AlarmClock ac(9900);
    vector<int> move;
    //make copy of Scaffold bc of const modifier
    Scaffold copy = s;
    move = determineBestMove(ac, copy, N, color, 0);
    return move[1];
}

//******************** Player derived class functions *************************

//  These functions simply delegate to the Impl classes' functions.
//  You probably don't want to change any of this code.

HumanPlayer::HumanPlayer(string nm)
 : Player(nm)
{
    m_impl = new HumanPlayerImpl;
}
 
HumanPlayer::~HumanPlayer()
{
    delete m_impl;
}
 
int HumanPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

BadPlayer::BadPlayer(string nm)
 : Player(nm)
{
    m_impl = new BadPlayerImpl;
}
 
BadPlayer::~BadPlayer()
{
    delete m_impl;
}
 
int BadPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}

SmartPlayer::SmartPlayer(string nm)
 : Player(nm)
{
    m_impl = new SmartPlayerImpl;
}
 
SmartPlayer::~SmartPlayer()
{
    delete m_impl;
}
 
int SmartPlayer::chooseMove(const Scaffold& s, int N, int color)
{
    return m_impl->chooseMove(s, N, color);
}
