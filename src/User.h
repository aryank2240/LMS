//
// Created by aryan on 3/6/2025.
//

#ifndef USER_H
#define USER_H
#include<bits/stdc++.h>
using namespace std;
#include "Account.h"



class User : public Account
{
protected:
    string id;
    string username;
    string password;
    string type;
public:

    virtual void incCount() = 0;
    virtual void decCount() = 0;
    string getUsername();
    int getFine() override;
    int getBorrowedBooksSize();
    string getId();
    vector<Books> getBorrowedBooks();
    int getSpace() override;
    void changePassword(string password);
    string getPassword();
    string getType();
    void setBooks(vector<Books> books);
    void setId(string id);
};



#endif //USER_H
