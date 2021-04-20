//
//  Set.h
//  Project 2
//
//  Created by Hender Lin on 4/14/21.
//

#ifndef SET_INCLUDED
#define SET_INCLUDED

#include <string>
using ItemType = std::string;

const int DEFAULT_MAX_ITEMS = 150;

class Set
{
  public:
    Set(int capacity = DEFAULT_MAX_ITEMS);
    int size() const;
    bool empty() const;
    bool insert(const ItemType& value);
    bool erase(const ItemType& value);
    bool contains(const ItemType& value) const;
    bool get(int i, ItemType& value) const;
    void swap(Set& other);

    Set(const Set& other);
    Set& operator=(const Set& other);
    ~Set();
    
  private:
    struct Node
    {
        ItemType m_data;
        Node *next;
        Node *prev;
    };
    
    int m_size;
    Node *head;
    Node *tail;
};

void unite(const Set& s1, const Set& s2, Set& result);

void difference(const Set& s1, const Set& s2, Set& result);

#endif /* Set_h */
