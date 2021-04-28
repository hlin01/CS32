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
    char prev = '/'; //prev char that isn't blank
    int open = 0; //open parentheses
    int close = 0; //closed parentheses
    int empty = 0; //empty spaces in infix
    //check if infix is empty
    if (infix.empty())
    {
        return false;
    }
    //loop through each character in infix
    for (int i = 0; i != infix.length(); i++)
    {
        ch = infix[i];
        //check if closed brackets outnumber open brackets at any point
        if (close > open)
        {
            return false;
        }
        //for each case, check if prev char is acceptable then set current char to prev
        switch (ch)
        {
            case ' ':
                empty++;
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
        //check if infix ends in an operator
        if (i+1 == infix.length() && (prev == '&' || prev == '^' || prev == '!'))
        {
            return false;
        }
    }
    //checks if infix is just blanks
    if (empty >= infix.length())
    {
        return false;
    }
    //checks if there are the same number of open and closed brackets
    if (open != close)
    {
        return false;
    }
    return true;
}

int precedence(char ch)
{
    //returns the precedence of operators
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
    //check if validInfix
    if (validInfix(infix) == false)
    {
        return 1;
    }
    //comments below would be redundant as code follows given Carrano's psuedocode
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
                while (!oprtr.empty() && oprtr.top() != '(' && precedence(ch) <= precedence(oprtr.top()))
                {
                    postfix += oprtr.top();
                    oprtr.pop();
                }
                oprtr.push(ch);
                break;
            case '!':
                while (!oprtr.empty() && oprtr.top() != '(' && precedence(ch) < precedence(oprtr.top()))
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
            char op1 = '/';
            if (!oprnd.empty())
            {
                op1 = oprnd.top();
                oprnd.pop();
            }
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
