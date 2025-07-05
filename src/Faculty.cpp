//
// Created by aryan on 3/6/2025.
//

#include "Faculty.h"

#include<bits/stdc++.h>

#include <utility>
using namespace std;
#include "User.h"

Faculty::Faculty( string username, string password)
{
    string temp= to_string(FacultyCount);
    temp+="Faculty";
    this-> id =temp;
    this->username = std::move(username);
    this->password = std::move(password);
    this->space = 5;
    this->fine = 0;
    this->type = "Faculty";
}
void Faculty::incCount() {
    FacultyCount++;
}
void Faculty::decCount()
{
    FacultyCount--;
}
void Faculty::setSpace(int substitute)
{
    if(substitute>0){
        this->space=substitute;
    }
    else{
        this->space -= 1;
    }
}