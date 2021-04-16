//
//  main.cpp
//  Homework 1
//
//  Created by Hender Lin on 4/11/21.
//

#include <iostream>
#include <string>
#include "Set.h"
using namespace std;

Set::Set()
{
    m_length = 0;
}

bool Set::empty() const
{
    if (m_length == 0)
    {
        return true;
    }
    return false;
}

int Set::size() const
{
    return m_length;
}

bool Set::insert(const ItemType& value)
{
    if (m_length >= DEFAULT_MAX_ITEMS)
    {
        return false;
    }
    if (m_length == 0)
    {
        m_set[0] = value;
        m_length++;
        return true;
    }
    if (contains(value))
    {
        return false;
    }
    for (int i = 0; i < m_length; i++)
    {
        if (m_set[i] > value)
        {
            for (int j = m_length; j > i; j--)
            {
                m_set[j] = m_set[j - 1];
            }
            m_set[i] = value;
            m_length++;
            return true;
        }
    }
    m_set[m_length] = value;
    m_length++;
    return true;
}

bool Set::erase(const ItemType& value)
{
    for (int i = 0; i < m_length; i++)
    {
        if (m_set[i] == value)
        {
            for (int j = i; j < m_length - 1; j++)
            {
                m_set[j] = m_set[j + 1];
            }
            m_length--;
            return true;
        }
    }
    return false;
}

bool Set::contains(const ItemType& value) const
{
    for (int i = 0; i < m_length; i++)
    {
        if (m_set[i] == value)
        {
            return true;
        }
    }
    return false;
}

bool Set::get(int i, ItemType& value) const
{
    if (i < 0 || i >= m_length)
    {
        return false;
    }
    value = m_set[m_length-1-i];
    return true;
}

void Set::swap(Set& other)
{
    int max;
    if (this->size() > other.size())
    {
        max = this->size();
    }
    else
    {
        max = other.size();
    }
    for (int i = 0; i < max; i++)
    {
        std::swap(this->m_set[i], other.m_set[i]);
    }
    std::swap(this->m_length, other.m_length);
}
