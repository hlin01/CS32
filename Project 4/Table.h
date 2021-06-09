//
//  Table.h
//  Project 4
//
//  Created by Hender Lin on 6/5/21.
//

#ifndef Table_h
#define Table_h
#include <string>
#include <vector>
#include <list>

class Table
    {
      public:
        Table(std::string keyColumn, const std::vector<std::string>& columns);
        ~Table();
        bool good() const;
        bool insert(const std::string& recordString);
        void find(std::string key, std::vector<std::vector<std::string>>& records) const;
        int select(std::string query, std::vector<std::vector<std::string>>& records) const;
        
          // We prevent a Table object from being copied or assigned by
          // making the copy constructor and assignment operator unavailable.
        Table(const Table&) = delete;
        Table& operator=(const Table&) = delete;
      private:
        int m_key = -1;
        int buckets = 0;
        std::vector<std::string> fields;
        std::list<std::vector<std::string>> *m_table;
        bool validRecord(const std::string& recordString);
        bool validQuery(std::string query) const;
    };

#endif /* Table_h */
