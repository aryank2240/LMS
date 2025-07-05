//
// Created by aryan on 3/6/2025.
//

#include "Books.h"
#include <bits/stdc++.h>
using namespace std;
Books::Books(string title, string author, string publisher, time_t Date, string ISBN) {
    this->title = title;
    this->author = author;
    this->publisher = publisher;
    this->Date = time(0);
    this->ISBN = ISBN;
    this->status = "Available";
}


string Books::getTitle() { return title; }
string Books::getAuthor() { return author; }
string Books::getPublisher() { return publisher; }
time_t Books::getYear() { return Date; }
string Books::getStatus() { return status; }
bool Books::checkAvailability() { return status == "Available"; }

void Books::saveBook() {
    ofstream file("Data/src/Books.txt", ios::app);
    file << title << " " << author << " " << publisher << " " << Date << " " << ISBN << " " << status << endl;
    file.close();
}

void Books::DisplayBook() {
    cout << "Title: " << title << endl;
    cout << "Author: " << author << endl;
    cout << "Publisher: " << publisher << endl;
    cout << "Date: " << Date << endl;
    cout << "ISBN: " << ISBN << endl;
    cout << "Status: " << status << endl;
}

void Books::setStatus(string newStatus) {
    status = newStatus;
}

void Books::setDate(time_t Date) {
    this->Date = Date;
}