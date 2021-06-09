//
//  main.cpp
//  Project 4
//
//  Created by Hender Lin on 6/5/21.
//

#include "Table.h"
#include <iostream>
#include <functional>
#include <algorithm>
#include <cstdlib>
#include <cctype>
#include <cassert>
using namespace std;

class StringParser
{
  public:
    StringParser(std::string text = "")
    {
        setString(text);
    }

    void setString(std::string text)
    {
        m_text = text;
        m_start = 0;
    }

    bool getNextField(std::string& field);

  private:
    std::string m_text;
    size_t m_start;
};

bool StringParser::getNextField(std::string& fieldText)
{
    m_start = m_text.find_first_not_of(" \t\r\n", m_start);
    if (m_start == std::string::npos)
    {
        m_start = m_text.size();
        fieldText = "";
        return false;
    }
    if (m_text[m_start] != '\'')
    {
        size_t end = m_text.find_first_of(" \t\r\n", m_start+1);
        fieldText = m_text.substr(m_start, end-m_start);
        m_start = end;
        return true;
    }
    fieldText = "";
    for (;;)
    {
        m_start++;
        size_t end = m_text.find('\'', m_start);
        fieldText += m_text.substr(m_start, end-m_start);
        m_start = (end != std::string::npos ? end+1 : m_text.size());
        if (m_start == m_text.size()  ||  m_text[m_start] != '\'')
            break;
        fieldText += '\'';
    }
    return true;
}

Table::Table(string keyColumn, const vector<string>& columns)
{
    //return if no fields are entered
    if (columns.size() == 0)
    {
        return;
    }
    for (int i = 0; i != columns.size(); i++)
    {
        //checks if field is empty string
        if (columns[i] == "")
        {
            return;
        }
        //sets key column
        if (columns[i] == keyColumn)
        {
            m_key = i;
        }
        for (int j = i+1; j != columns.size(); j++)
        {
            //checks for duplicate columns
            if (columns[i] == columns[j])
            {
                return;
            }
        }
    }
    //if no key was set, return
    if (m_key < 0)
    {
        return;
    }
    //sets buckets and fields
    buckets = 997;
    fields = columns;
    //initialize table
    m_table= new list<vector<string>> [buckets];
}

bool Table::good() const
{
    //if buckets is not 0, table was well-formed
    if (buckets > 0)
    {
        return true;
    }
    return false;
}

Table::~Table() {};

bool Table::validRecord(const string& recordString)
{
    StringParser parser(recordString);
    string s;
    int num = 0;
    //counts the number of fields and returns appropriate bool
    while (parser.getNextField(s))
    {
        num++;
    }
    if (num == fields.size())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Table::insert(const string& recordString)
{
    //if not valid record or bad table, return false
    if (!validRecord(recordString) || !good())
    {
        return false;
    }
    StringParser parser(recordString);
    string s;
    vector<string> v;
    unsigned long h = -1;
    //loop through parsed record
    for (int i = 0; i != fields.size(); i++)
    {
        parser.getNextField(s);
        //if parsed string is key column, hash it
        if (i == m_key)
        {
            h = hash<string>()(s);
        }
        //push parsed string onto vector to be stored
        v.push_back(s);
    }
    //modulo operator and push record vector onto table
    h = h % buckets;
    m_table[h].push_back(v);
    return true;
}

void Table::find(string key, vector<vector<string>>& records) const
{
    //set records to empty vector
    records = {};
    //return if bad table
    if (!good())
    {
        return;
    }
    list<vector<string>>::iterator it;
    vector<string> entry;
    //get to the bucket given the key
    unsigned long h = hash<string>()(key);
    h = h % buckets;
    //loop through list at bucket
    for (it = m_table[h].begin(); it != m_table[h].end(); it++)
    {
        entry = *it;
        //if field is equal to the key, push it onto records
        if (entry[m_key] == key)
        {
            records.push_back(*it);
        }
    }
}

bool stringToDouble(string s, double& d)
{
    char* end;
    d = std::strtof(s.c_str(), &end);
    return end == s.c_str() + s.size()  &&  !s.empty();
}

bool Table::validQuery(string query) const
{
    StringParser parser(query);
    string s;
    int numerical = 0;
    //loop through 3 token query
    for (int i = 0; i != 3; i++)
    {
        //checks if parsed query has at least 3 fields
        if (!parser.getNextField(s))
        {
            return false;
        }
        //checks if first parsed string is a field
        if (i == 0)
        {
            for (int j = 0; j != fields.size(); j++)
            {
                if (fields[j] == s)
                {
                    break;
                }
                else if (j == fields.size()-1)
                {
                    return false;
                }
            }
        }
        //checks if second parsed string is an operator
        if (i == 1)
        {
            if (s == "<" || s == "<=" || s == ">" || s == ">=" || s == "!=" || s == "==" || s == "=")
            {
                continue;
            }
            //make second parsed string uppercase
            for (int i = 0; i != s.length(); i++)
            {
                s[i] = toupper(s[i]);
            }
            if (s == "LT" || s == "LE" || s == "GT" || s == "GE" || s == "NE" || s == "EQ")
            {
                //if second parsed string is one of these operators, remember that operands must be numerical
                numerical = 1;
                continue;
            }
            return false;
        }
        if (i == 2)
        {
            double d;
            //if query is numerical and third parsed string is not a proper number, return false
            if (numerical == 1 && !stringToDouble(s, d))
            {
                return false;
            }
            //checks if parsed query has 3 fields at most
            if (parser.getNextField(s))
            {
                return false;
            }
        }
    }
    return true;
}

int Table::select(string query, vector<vector<string>>& records) const
{
    //set records to empty vector
    records = {};
    //check if query is valid and table is well-formed
    if (!validQuery(query) || !good())
    {
        return -1;
    }
    StringParser parser(query);
    string s1;
    string s2;
    string s3;
    parser.getNextField(s1);
    parser.getNextField(s2);
    parser.getNextField(s3);
    int newkey = -1;
    //set the key field being examined
    for (int i = 0; i != fields.size(); i++)
    {
        if (fields[i] == s1)
        {
            newkey = i;
        }
    }
    //make operator uppercase if needed
    for (int i = 0; i != s2.length(); i++)
    {
        s2[i] = toupper(s2[i]);
    }
    list<vector<string>>::iterator it;
    vector<string> entry;
    int bad = 0;
    double op1;
    double op2;
    //linear search through each bucket and linked list
    for (int i = 0; i != buckets; i++)
    {
        for (it = m_table[i].begin(); it != m_table[i].end(); it++)
        {
            entry = *it;
            //for all string comparisons below, if examined element fulfills condition, push it onto records
            if (s2 == "<")
            {
                if (entry[newkey] < s3)
                {
                    records.push_back(entry);
                }
                continue;
            }
            if (s2 == "<=")
            {
                if (entry[newkey] <= s3)
                {
                    records.push_back(entry);
                }
                continue;
            }
            if (s2 == ">")
            {
                if (entry[newkey] > s3)
                {
                    records.push_back(entry);
                }
                continue;
            }
            if (s2 == ">=")
            {
                if (entry[newkey] >= s3)
                {
                    records.push_back(entry);
                }
                continue;
            }
            if (s2 == "!=")
            {
                if (entry[newkey] != s3)
                {
                    records.push_back(entry);
                }
                continue;
            }
            if (s2 == "=" || s2 == "==")
            {
                if (entry[newkey] == s3)
                {
                    records.push_back(entry);
                }
                continue;
            }
            //for all numerical comparisons below, if third parsed string (second operand) is a proper number and fulfills condition, push it onto records, otherwise increment bad query counter
            if (s2 == "LT")
            {
                stringToDouble(s3, op2);
                if (stringToDouble(entry[newkey], op1))
                {
                    if (op1 < op2)
                    {
                        records.push_back(entry);
                    }
                }
                else
                {
                    bad++;
                }
                continue;
            }
            if (s2 == "LE")
            {
                stringToDouble(s3, op2);
                if (stringToDouble(entry[newkey], op1))
                {
                    if (op1 <= op2)
                    {
                        records.push_back(entry);
                    }
                }
                else
                {
                    bad++;
                }
                continue;
            }
            if (s2 == "GT")
            {
                stringToDouble(s3, op2);
                if (stringToDouble(entry[newkey], op1))
                {
                    if (op1 > op2)
                    {
                        records.push_back(entry);
                    }
                }
                else
                {
                    bad++;
                }
                continue;
            }
            if (s2 == "GE")
            {
                stringToDouble(s3, op2);
                if (stringToDouble(entry[newkey], op1))
                {
                    if (op1 >= op2)
                    {
                        records.push_back(entry);
                    }
                }
                else
                {
                    bad++;
                }
                continue;
            }
            if (s2 == "NE")
            {
                stringToDouble(s3, op2);
                if (stringToDouble(entry[newkey], op1))
                {
                    if (op1 != op2)
                    {
                        records.push_back(entry);
                    }
                }
                else
                {
                    bad++;
                }
                continue;
            }
            if (s2 == "EQ")
            {
                stringToDouble(s3, op2);
                if (stringToDouble(entry[newkey], op1))
                {
                    if (op1 == op2)
                    {
                        records.push_back(entry);
                    }
                }
                else
                {
                    bad++;
                }
                continue;
            }
        }
    }
    return bad;
}
