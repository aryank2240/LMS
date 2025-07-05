//
// Created by aryan on 3/6/2025.
//

#ifndef ACCOUNT_H
#define ACCOUNT_H
#include "Books.h"
#include<bits/stdc++.h>
using namespace std;
class Account {
public:
    int space;
    int fine;
    vector<Books> borrowedBooks;
    virtual int getFine()=0;
    virtual int getSpace()=0;
    void addBook(Books book);
    void RemoveBook(Books book);
    Books borrowBook(string title);
    Books returnBook(string title);
};


#endif //ACCOUNT_H
