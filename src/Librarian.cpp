//
// Created by aryan on 3/6/2025.
//

#include "Librarian.h"
#include<bits/stdc++.h>

#include <utility>
using namespace std;
#include"User.h"


Librarian::Librarian(int id, string username, string password)
{
    this->id = id;
    this->username = std::move(username);
    this->password = std::move(password);
}
void Librarian::borrowBook(Books book)
{
    cout << "Librarian can't borrow books" << endl;
}
void Librarian::returnBook(Books book)
{
    cout << "Librarian can't return books" << endl;
}
void Librarian::IncreaseFine()
{
    cout << "Librarian can't have fine" << endl;
}
void Librarian::DecreaseFine()
{
    cout << "Librarian can't have fine" << endl;
}