//
//  AccountSet.h
//  Homework 1
//
//  Created by Hender Lin on 4/11/21.
//

#ifndef AccountSet_h
#define AccountSet_h

#include "Set.h"

class AccountSet
    {
      public:
        AccountSet();  // Create an empty account set.

        bool add(ItemType acctNum);
          // Add an account number to the AccountSet.  Return true if and
          // only if the account number was actually added.

        int size() const;
          // Return the number of account numbers in the AccountSet.

        void print() const;
          // Write to cout every account number in the AccountSet exactly
          // once, one per line.  Write no other text.

      private:
        Set m_accset;
        // Some of your code goes here.
    };

#endif /* AccountSet_h */
