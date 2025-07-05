//
// Created by aryan on 3/6/2025.
//

#ifndef LIBRARIAN_H
#define LIBRARIAN_H
#include<bits/stdc++.h>
using namespace std;
#include"User.h"


class Librarian : public User
{
public:
    static int LibrarianCount;
    Librarian(int id, string username, string password);
    static void borrowBook(Books book);

    static void returnBook(Books book);
    static void IncreaseFine();
    static void DecreaseFine();
};

#endif //LIBRARIAN_H
