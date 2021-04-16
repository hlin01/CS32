//
//  AccountSet.cpp
//  Homework 1
//
//  Created by Hender Lin on 4/11/21.
//

#include <iostream>
#include <string>
#include "AccountSet.h"
using namespace std;

AccountSet::AccountSet(){
}

bool AccountSet::add(ItemType acctNum)
{
    return m_accset.insert(acctNum);
}

int AccountSet::size() const
{
    return m_accset.size();
}

void AccountSet::print() const
{
    for (int i = 0; i < m_accset.size(); i++)
    {
        ItemType j;
        m_accset.get(i, j);
        cout << j << endl;
    }
}
