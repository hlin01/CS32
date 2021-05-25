//
//  bad.cpp
//  Homework 4
//
//  Created by Hender Lin on 5/9/21.
//

void removeBad(list<Movie*>& li)
{
    list<Movie*>::iterator it = li.begin();
    while (it != li.end())
    {
        if ((*it)->rating() < 55)
        {
            (*it)->~Movie();
            li.erase(it);
        }
        it++;
    }
}
