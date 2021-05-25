//
//  list.cpp
//  Homework 4
//
//  Created by Hender Lin on 5/23/21.
//

void listAll(string path, const MenuItem* m) // two-parameter overload
{
    if (m->name() != "")
    {
        cout << path << m->name() << endl;
    }
    if (m->menuItems() == nullptr || m->menuItems()->size() == 0)
    {
        return;
    }
    if (m->name() != "")
    {
        path += m->name() + "/";
    }
    for (MenuItem* menuItemPtr : *(m->menuItems()))
    {
        listAll(path, menuItemPtr);
    }
}
