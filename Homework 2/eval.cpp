//
//  eval.cpp
//  Homework 2
//
//  Created by Hender Lin on 4/24/21.
//

#include <iostream>
#include <string>
#include <stack>
#include <cassert>
using namespace std;

bool validInfix(string infix)
{
    char ch;
    char prev = '/';
    int open = 0;
    int close = 0;
    if (infix.empty())
    {
        return false;
    }
    for (int i = 0; i != infix.length(); i++)
    {
        ch = infix[i];
        switch (ch)
        {
            case ' ':
                break;
            case 'T':
            case 'F':
                if (prev == 'T' || prev == 'F' || prev == ')')
                {
                    return false;
                }
                prev = ch;
                break;
            case '(':
                if (prev == 'T' || prev == 'F' || prev == ')')
                {
                    return false;
                }
                prev = ch;
                open++;
                break;
            case ')':
                if (prev != 'T' && prev != 'F' && prev != ')')
                {
                    return false;
                }
                prev = ch;
                close++;
                break;
            case '&':
            case '^':
                if (prev != 'T' && prev != 'F' && prev != ')')
                {
                    return false;
                }
                prev = ch;
                break;
            case '!':
                if (prev == 'T' || prev == 'F' || prev == ')')
                {
                    return false;
                }
                prev = ch;
                break;
            default:
                return false;
                
        }
        if (i+1 == infix.length() && (prev == '&' || prev == '^' || prev == '!'))
        {
            return false;
        }
    }
    if (open != close)
    {
        return false;
    }
    return true;
}

int precedence(char ch)
{
    switch (ch)
    {
        case '!':
            return 3;
        case '&':
            return 2;
        case '^':
            return 1;
        default:
            return -1;
    }
}

int evaluate(string infix, string& postfix, bool& result)
{
    if (validInfix(infix) == false)
    {
        return 1;
    }
    postfix = "";
    stack<char> oprtr;
    for (int i = 0; i != infix.length(); i++)
    {
        char ch = infix[i];
        switch (ch)
        {
            case ' ':
                break;
            case 'T':
            case 'F':
                postfix += ch;
                break;
            case '(':
                oprtr.push(ch);
                break;
            case ')':
                while (oprtr.top() != '(')
                {
                    postfix += oprtr.top();
                    oprtr.pop();
                }
                oprtr.pop();
                break;
            case '&':
            case '^':
            case '!':
                while (!oprtr.empty() && oprtr.top() != '(' && precedence(ch) <= precedence(oprtr.top()))
                {
                    postfix += oprtr.top();
                    oprtr.pop();
                }
                oprtr.push(ch);
                break;
            default:
                return 1;
        }
    }
    while (!oprtr.empty())
    {
        postfix += oprtr.top();
        oprtr.pop();
    }
    stack<char> oprnd;
    for (int i = 0; i != postfix.length(); i++)
    {
        char ch = postfix[i];
        if (ch == 'T')
        {
            oprnd.push(true);
        }
        else if (ch == 'F')
        {
            oprnd.push(false);
        }
        else
        {
            char op2 = oprnd.top();
            oprnd.pop();
            char op1 = oprnd.top();
            oprnd.pop();
            if (ch == '&')
            {
                oprnd.push(op1 & op2);
            }
            else if (ch == '^')
            {
                oprnd.push(op1 ^ op2);
            }
            else
            {
                oprnd.push(op1);
                oprnd.push(!op2);
            }
        }
    }
    result = oprnd.top();
    return 0;
}
