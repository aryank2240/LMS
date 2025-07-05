//
// Created by aryan on 3/6/2025.
//

#include "Students.h"
#include<bits/stdc++.h>

#include <utility>
using namespace std;

Students::Students( string username, string password)
{
    string temp= to_string(StudentsCount);
    temp+="Student";
    this-> id =temp;
    this->username = std::move(username);
    this->password = std::move(password);
    this->space = 3;
    this->fine = 0;
    this->type = "Students";
}


void Students::incCount() 
{
    StudentsCount++;
}
void Students::decCount() 
{
    StudentsCount--;
}

void Students::IncreaseFine(int substitute)
{
    if(substitute>=0){
        this->fine=substitute;
    }
    else{
        this->fine += 10;
    }

}
void Students::DecreaseFine(int substitute)
{
    if(substitute>=0){
        this->fine-=substitute;
    }
    else{
        this->fine -= 10;
    }
}
void Students::setSpace(int substitute)
{
    if(substitute>0){
        this->space=substitute;
    }
    else{
        this->space -= 1;
    }
}