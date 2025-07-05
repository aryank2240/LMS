//
// Created by aryan on 3/6/2025.
//

#include "Account.h"
#include <bits/stdc++.h>
using namespace std;
string Basepath2="E:/";

string Bookpath2=Basepath2+"untitled1/src/Data/Books.txt";
void Account::addBook(Books book)
{
    borrowedBooks.push_back(book);
}
void Account::RemoveBook(Books book)
{
    for (int i = 0; i < borrowedBooks.size(); i++)
    {
        if (borrowedBooks[i].getTitle() == book.getTitle())
        {
            borrowedBooks.erase(borrowedBooks.begin() + i);
            break;
        }
    }
}
Books Account::borrowBook(string title)
{   int flag=0;
    if (this->space > 0)
    {
        if (this->fine <= 0)
        {   
            ifstream file(Bookpath2);
            if (!file)
            {
                cerr << "Error opening file!" << endl;
                return Books("", "", "", 0, "");
            }
            vector<Books> books;
            string line, fileTitle, author, publisher, ISBN, status;
            time_t Date;
            Books borrowedBook("", "", "", 0, "");

            while (getline(file, line))
            {
                stringstream ss(line);
                ss >> fileTitle >> author >> publisher >> Date >> ISBN >> status;
                Books book(fileTitle, author, publisher, Date, ISBN);
                book.setStatus(status);
                book.setDate(Date);
                if (fileTitle == title && status == "Available")
                {
                    
                    book.setStatus("Borrowed");
                    borrowedBook = book;

                }
                else if(fileTitle == title && status == "Borrowed")
                {
                    cout<<"Book has been borrowed by another user."<<endl<<"please choose another book"<<endl;
                    book.setStatus("Borrowed");
                    flag=1;
                }
                books.push_back(book);
            }
            file.close();
            bool check = false;
            for(Books &b : books)
            {
                if(b.getTitle() == title)
                {
                    check=true;
                    break;
                }
            }
            if(!check)
            {
                cout<<"Book not found"<<endl;
                return {"", "", "", 0, ""};
            }
            ofstream outFile(Bookpath2);
            for (Books &b : books)
            {
                outFile << b.getTitle() << " " << b.getAuthor() << " " << b.getPublisher() << " "
                        << b.getYear() << " " << b.ISBN << " " << b.getStatus() << endl;
            }
            outFile.close();
            if(flag==1){
                return {"", "", "", 0, ""};
            }
            
            this->space--;
            return borrowedBook;
        }
        else
        {
            cout << "Please pay your fines first." << endl;
            return {"", "", "", 0, ""};
        }
    }

    else
    {
        cout << "You have reached the limit of borrowing books" << endl;
    }
    return {"", "", "", 0, ""};
}

Books Account::returnBook(string title)
{
    int flag=0;
    ifstream file(Bookpath2);
    if (!file)
    {
        cerr << "Error opening file!" << endl;
        return Books("", "", "", 0, "");
    }
    vector<Books> books;
    string line, fileTitle, author, publisher, ISBN, status;
    time_t Date;
    Books returnedBook("", "", "", 0, "");

    while (getline(file, line)) {
        stringstream ss(line);
        ss >> fileTitle >> author >> publisher >> Date >> ISBN >> status;
        Books book(fileTitle, author, publisher, Date, ISBN);
         book.setStatus(status);
        if (fileTitle == title && status == "Borrowed")
        {
            book.setStatus("Available");
            returnedBook = book;
        }
        else if(fileTitle == title && status == "Available")
        {
            cout<<"Book has already been returned."<<endl;
            flag=1;
        }
        books.push_back(book);
    }
    file.close();
    bool check = false;
    for(Books &b : books)
    {
        if(b.getTitle() == title)
        {
            check=true;
            break;
        }
    }
    if(!check)
    {
        cout<<"Book not found"<<endl;
        return {"", "", "", 0, ""};
    }
    ofstream outFile(Bookpath2);
    for (Books &b : books)
    {
        outFile << b.getTitle() << " " << b.getAuthor() << " " << b.getPublisher() << " "
                << b.getYear() << " " << b.ISBN << " " << b.getStatus() << endl;
    }
    outFile.close();
    this->space++;

    return returnedBook;
}