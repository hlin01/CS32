//
//  main.cpp
//  Project 2
//
//  Created by Hender Lin on 4/14/21.
//

#include "Set.h"
#include <iostream>
#include <cstdlib>
using namespace std;

Set::Set(int capacity)
{
    head = nullptr;
    tail = nullptr;
    m_size = 0;
}

int Set::size() const
{
    return m_size;
}

bool Set::empty() const
{
    return size() == 0;
}

bool Set::insert(const ItemType& value)
{
    if (head == nullptr)
    {
        Node* p = new Node;
        p->m_data = value;
        p->prev = nullptr;
        p->next = nullptr;
        head = p;
        tail = p;
        m_size++;
        return true;
    }
    if (value < head->m_data)
    {
        Node *p = head;
        Node *n = new Node;
        n->m_data = value;
        n->prev = nullptr;
        n->next = p;
        p->prev = n;
        head = n;
        m_size++;
        return true;
    }
    Node *p;
    for (p = head; p->next != nullptr; p = p->next)
    {
        if (p->m_data == value || p->next->m_data == value)
        {
            return false;
        }
        if (p->next->m_data > value)
        {
            Node* n = new Node;
            n->m_data = value;
            n->prev = p;
            n->next = p->next;
            p->next = n;
            p->next->next->prev = n;
            m_size++;
            return true;
        }
    }
    Node *n = new Node;
    n->m_data = value;
    n->prev = p;
    n->next = nullptr;
    p->next = n;
    tail = n;
    m_size++;
    return true;
}

bool Set::erase(const ItemType& value)
{
    if(!contains(value))
    {
        return false;
    }
    Node* p;
    for (p = head; p != nullptr; p = p->next)
    {
        if (p->m_data == value)
            break;
    }
    if (p->prev != nullptr)
    {
        p->prev->next = p->next;
    }
    else
    {
        head = p->next;
    }
    if (p->next != nullptr)
    {
        p->next->prev = p->prev;
    }
    else
    {
        tail = p->prev;
    }
    m_size--;
    delete p;
    return true;
}

bool Set::contains(const ItemType& value) const
{
    Node *p;
    for (p = head; p != nullptr; p = p->next)
    {
        if (p->m_data == value)
        {
            return true;
        }
    }
    return false;
}

bool Set::get(int i, ItemType& value) const
{
    if (i < 0 || i >= m_size)
    {
        return false;
    }
    Node *p = head;
    for (int j = 0; j != m_size-1-i; j++)
    {
        p = p->next;
    }
    value = p->m_data;
    return true;
}

void Set::swap(Set& other)
{
    int t_size = m_size;
    m_size = other.m_size;
    other.m_size = t_size;
    Node* t_head = head;
    head = other.head;
    other.head = t_head;
    Node* t_tail = tail;
    tail = other.tail;
    other.tail = t_tail;
}

Set::Set(const Set& other)
{
    if (other.m_size == 0)
    {
        head = nullptr;
        tail = nullptr;
        return;
    }
    m_size = other.m_size;
    head = new Node;
    head->prev = nullptr;
    Node* t_node = head;
    for (Node* p = other.head; p->next != nullptr; p = p->next)
    {
        Node* n_node = new Node;
        t_node->m_data = p->m_data;
        t_node->next = n_node;
        n_node->prev = t_node;
        t_node = n_node;
    }
    t_node->m_data = other.tail->m_data;
    t_node->next = nullptr;
    tail = t_node;
}

Set& Set::operator=(const Set& other)
{
    if (this != &other)
    {
        Set temp(other);
        swap(temp);
    }
    return *this;
}

Set::~Set()
{
    if (head == nullptr)
    {
        return;
    }
    Node *p = head;
    Node *n;
    while (p != nullptr)
    {
        n = p->next;
        delete p;
        p = n;
    }
}

void unite(const Set& s1, const Set& s2, Set& result)
{
    result = s1;
    ItemType temp;
    for (int i = 0; i != s2.size(); i++)
    {
        s2.get(i,temp);
        result.insert(temp);
    }
}

void difference(const Set& s1, const Set& s2, Set& result)
{
    if (&s1 == &s2)
    {
        Set empty;
        result = empty;
        return;
    }
    result = s1;
    ItemType temp;
    for (int i = 0; i != s2.size(); i++)
    {
        s2.get(i,temp);
        if (result.contains(temp))
        {
            result.erase(temp);
        }
        else
        {
            result.insert(temp);
        }
    }
}
