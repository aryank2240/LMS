//
// Created by aryan on 3/6/2025.
//

#ifndef BOOKS_H
#define BOOKS_H

#include<bits/stdc++.h>
using namespace std;

class Books {
private:
    string title;
    string author;
    string publisher;
    time_t Date;
    string status;

public:
    string ISBN;

    Books(string title, string author, string publisher, time_t Date, string ISBN);


    string getTitle();
    string getAuthor();
    string getPublisher();
    time_t getYear();
    string getStatus() ;
    bool checkAvailability();


    void saveBook();
    void setDate(time_t Date);

    void DisplayBook() ;

    void setStatus(string newStatus);
};


#endif //BOOKS_H
