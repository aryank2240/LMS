//
// Created by aryan on 3/6/2025.
//

#ifndef FACULTY_H
#define FACULTY_H
#include<bits/stdc++.h>
using namespace std;
#include "User.h"

class Faculty : public User
{
public:
    static int FacultyCount;
    Faculty( string username, string password);
    void incCount() override ;
    void decCount() override ;
    void setSpace(int substitute);
};




#endif //FACULTY_H
