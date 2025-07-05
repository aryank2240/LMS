//
// Created by aryan on 3/6/2025.
//

#ifndef STUDENTS_H
#define STUDENTS_H

#include<bits/stdc++.h>
using namespace std;
#include "User.h"

class Students : public User
{
public:
    static int StudentsCount;
    Students( string username, string password);
    void incCount() override ;
    void decCount() override ;

    void IncreaseFine(int substitute);
    void DecreaseFine(int substitute);
    void setSpace(int substitute);
};



#endif //STUDENTS_H
