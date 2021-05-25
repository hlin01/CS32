//
//  odds.cpp
//  Homework 4
//
//  Created by Hender Lin on 5/9/21.
//

void removeOdds(vector<int>& v)
{
    vector<int>::iterator it = v.begin();
    while (it != v.end())
    {
        if (*it % 2 == 1)
        {
            v.erase(it);
        }
        else
        {
            it++;
        }
    }
}
