//
// Created by aryan on 3/6/2025.
//

#include "User.h"
#include<bits/stdc++.h>

#include <utility>
using namespace std;

string User::getUsername() { return username; }
int User::getFine() { return fine; }

int User::getBorrowedBooksSize() { return borrowedBooks.size(); }
string User::getId() { return id; }
vector<Books> User::getBorrowedBooks() { return borrowedBooks; }
int User::getSpace() { return space; }
void User::changePassword(string password)
{
    this->password = std::move(password);
}
string User::getPassword() { return password; }
string User::getType() { return type; }
void User::setBooks(vector<Books> books) { borrowedBooks = books; }

void User::setId(string id) { this->id = std::move(id); }   