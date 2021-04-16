//
//  newSet.cpp
//  Homework 1
//
//  Created by Hender Lin on 4/12/21.
//

#include <iostream>
#include <string>
#include "newSet.h"
using namespace std;

Set::Set(int max)
{
    if (max < 0)
    {
        exit(1);
    }
    m_length = 0;
    m_max = max;
    m_set = new ItemType[max];
}

Set::Set(const Set &other)
{
    m_length = other.m_length;
    m_max = other.m_max;
    m_set = new ItemType[m_length];
    for (int i = 0; i < m_length; i++)
    {
        m_set[i] = other.m_set[i];
    }
}

Set &Set::operator=(const Set &other)
{
    if (&other == this)
    {
        return *this;
    }
    delete [] m_set;
    m_length = other.m_length;
    m_max = other.m_max;
    m_set = new ItemType[m_length];
    for (int i = 0; i < m_length; i++)
    {
        m_set[i] = other.m_set[i];
    }
    return *this;
}

Set::~Set()
{
    delete [] m_set;
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
    if (m_length >= m_max)
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
    std::swap(this->m_length, other.m_length);
    std::swap(this->m_max, other.m_max);
    std::swap(this->m_set, other.m_set);
}
