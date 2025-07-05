#include <bits/stdc++.h>
using namespace std;
#include "User.h"

#include "Books.h"
#include "Account.h"
#include "Students.h"
#include "Faculty.h"
#include "Librarian.h"
string Basepath="E:/";
string Accountpath=Basepath+"untitled1/src/Data/Accounts.txt";
string Bookpath=Basepath+"untitled1/src/Data/Books.txt";
string StaticDataPath=Basepath+"untitled1/src/Data/Static_data.txt";
Books getBook(string title)
{
    ifstream file(Bookpath);
    if (!file)
    {
        cerr << "Error opening file!" << endl;
        return {"", "", "", 0, ""};
    }
    string line, fileTitle, author, publisher, ISBN, status;
    time_t Date;
    while (getline(file, line))
    {
        stringstream ss(line);
        ss >> fileTitle >> author >> publisher >> Date >> ISBN >> status;
        if (fileTitle == title)
        {
            Books book(fileTitle, author, publisher, Date, ISBN);
            book.setDate(Date);
            book.setStatus(status);
            return book;
        }
    }
    return {"", "", "", 0, ""};
}

Books addBooks()
{
    string title, author, publisher, ISBN;
    time_t Date;
    cout << "Enter the title of the book: ";
    cin >> title;
    cout << "Enter the author of the book: ";
    cin >> author;
    cout << "Enter the publisher of the book: ";
    cin >> publisher;
    cout << "Enter the ISBN of the book: ";
    cin >> ISBN;
    Books book(title, author, publisher, time_t(0), ISBN);
    book.saveBook();
    return book;
}

void CreateAccount()
{
    string type;
    cout << "Enter the type of account you want to create: " << endl;
    cout << "1. student" << endl;
    cout << "2. Faculty" << endl;
    cin >> type;
    string username, password;

    if (type == "student")
    {
        cout << "Enter the username: ";
        cin >> username;
        cout << "Enter the password: ";
        cin >> password;
        Students Xstudent(username, password);

        ifstream file(Accountpath);
        if (!file)
        {
            cerr << "Error opening file!" << endl;
            return;
        }
        string id, tempusername, temptype, line;
        int fine, space;

        vector<Students> students;
        vector<Faculty> faculties;
        while (getline(file, line))
        {
            vector<Books> borrowedBooks;
            stringstream ss(line);
            ss >> id >> tempusername >> password >> fine >> space >> temptype;
            string bookTitle;
            while (ss >> bookTitle)
            {
                Books book = getBook(bookTitle);
                if (!book.getTitle().empty())
                {
                    borrowedBooks.push_back(book);
                }
                else
                {
                    cout << "Warning: The book titled '" << bookTitle << "' could not be found." << endl;
                }
            }
            if (temptype == "Students")
            {
                Students student(tempusername, password);
                student.IncreaseFine(fine);
                student.setSpace(space);
                student.setBooks(borrowedBooks);
                student.setId(id);
                students.push_back(student);
            }
            else{
                Faculty faculty(tempusername, password);
                faculty.setId(id);
                faculty.setSpace(space);
                faculty.setBooks(borrowedBooks);
                faculties.push_back(faculty);
            }
        }
        students.push_back(Xstudent);
        file.close();
        ofstream outFile(Accountpath);
        for (Students &s : students)
        {
            outFile << s.getId() << " " << s.getUsername() << " " << s.getPassword() << " " << s.getFine() << " " << s.getSpace() << " " << s.getType() << " ";
            for (Books &book : s.getBorrowedBooks())
            {
                outFile << book.getTitle() << " ";
            }
            outFile << endl;
        }
        for(Faculty &f : faculties)
        {
            outFile << f.getId() << " " << f.getUsername() << " " << f.getPassword() << " " << f.getFine() << " " << f.getSpace() << " " << f.getType() << " ";
            for (Books &book : f.getBorrowedBooks())
            {
                outFile << book.getTitle() << " ";
            }
            outFile << endl;
        }
        Xstudent.incCount();
        outFile.close();
    }
    else if (type == "Faculty")
    {
        cout << "Enter the username: ";
        cin >> username;
        cout << "Enter the password: ";
        cin >> password;
        Faculty faculty(username, password);

        ifstream file(Accountpath);
        if (!file)
        {
            cerr << "Error opening file!" << endl;
            return;
        }
        string id, tempusername, temptype, line;
        int fine, space;

        vector<Faculty> faculties;
        vector<Students> students;
        while (getline(file, line))
        {
            vector<Books> borrowedBooks;
            stringstream ss(line);
            ss >> id >> tempusername >> password >> fine >> space >> temptype;
            string bookTitle;
            while (ss >> bookTitle)
            {
                Books book = getBook(bookTitle);
                if (!book.getTitle().empty())
                {
                    borrowedBooks.push_back(book);
                }
                else
                {
                    cout << "Warning: The book titled '" << bookTitle << "' could not be found." << endl;
                }
            }
            if (temptype == "Faculty")
            {
                Faculty faculty(tempusername, password);
                faculty.setId(id);
                faculty.setSpace(space);
                faculty.setBooks(borrowedBooks);
                faculties.push_back(faculty);
            }
            else{
                Students student(tempusername, password);
                student.IncreaseFine(fine);
                student.setSpace(space);
                student.setBooks(borrowedBooks);
                student.setId(id);
                students.push_back(student);
            }
        }
        faculties.push_back(faculty);
        file.close();
        ofstream outFile(Accountpath);
        for (Faculty &f : faculties)
        {
            outFile << f.getId() << " " << f.getUsername() << " " << f.getPassword() << " " << f.getFine() << " " << f.getSpace() << " " << f.getType() << " ";
            for (Books &book : f.getBorrowedBooks())
            {
                outFile << book.getTitle() << " ";
            }
            outFile << endl;
        }
        for(Students &s : students)
        {
            outFile << s.getId() << " " << s.getUsername() << " " << s.getPassword() << " " << s.getFine() << " " << s.getSpace() << " " << s.getType() << " ";
            for (Books &book : s.getBorrowedBooks())
            {
                outFile << book.getTitle() << " ";
            }
            outFile << endl;
        }
        faculty.incCount();
        outFile.close();
    }
    else
    {
        cout << "Invalid type" << endl;
        CreateAccount();
    }
}
Students getStudentbyId(string ID, string type){
    ifstream file(Accountpath);
    if (!file)
    {
        cerr << "Error opening file!" << endl;
    }
    else
    {
        if (type == "Students")
        {
            vector<Students> students;
            string line, tempusername, password, temptype;
            string tempid;
            int fine, space;

            while (getline(file, line))
            {
                vector<Books> borrowedBooks;
                stringstream ss(line);
                ss >> tempid >> tempusername >> password >> fine >> space >> temptype;
                string bookTitle;
                while (ss >> bookTitle)
                {
                    Books book = getBook(bookTitle);
                    if (!book.getTitle().empty())
                    {
                        borrowedBooks.push_back(book);
                    }
                    else
                    {
                        cout << "Warning: The book titled '" << bookTitle << "' could not be found." << endl;
                    }
                }
                if (temptype == "Students")
                {
                    Students student(tempusername, password);
                    student.IncreaseFine(fine);
                    student.setSpace(space);
                    student.setBooks(borrowedBooks);
                    student.setId(tempid);
                    students.push_back(student);
                }
            }
            file.close();
            for (Students &s : students)
            {
                if (s.getId() == ID)
                {
                    return s;
                }
            }
            cout << "Student not found" << endl;
        }
        else
        {
            cout << "Invalid type" << endl;
        }
    }
}
Students getStudent(string username, string type)
{
    ifstream file(Accountpath);
    if (!file)
    {
        cerr << "Error opening file!" << endl;
    }
    else
    {
        if (type == "Students")
        {
            vector<Students> students;
            string line, tempusername, password, temptype;
            string id;
            int fine, space;

            while (getline(file, line))
            {
                vector<Books> borrowedBooks;
                stringstream ss(line);
                ss >> id >> tempusername >> password >> fine >> space >> temptype;
                string bookTitle;
                while (ss >> bookTitle)
                {
                    Books book = getBook(bookTitle);
                    if (book.getTitle()!="")
                    {
                        borrowedBooks.push_back(book);
                    }
                    else
                    {
                        cout << "Warning: The book titled '" << bookTitle << "' could not be found." << endl;
                    }
                }
                if (temptype == "Students")
                {
                    Students student(tempusername, password);
                    student.IncreaseFine(fine);
                    student.setSpace(space);
                    student.setBooks(borrowedBooks);
                    student.setId(id);
                    students.push_back(student);
                }
            }
            file.close();
            for (Students &s : students)
            {
                if (s.getUsername() == username)
                {
                    return s;
                }
            }
            cout << "Student not found" << endl;
        }
        else
        {
            cout << "Invalid type" << endl;
        }
    }
    return {"", ""};
}



Faculty getFacultybyID(string ID,string type){
    ifstream file(Accountpath);
    if (!file)
    {
        cerr << "Error opening file!" << endl;
    }
    else
    {
        if (type == "Faculty")
        {
            vector<Faculty> faculties;
            string line, tempusername, password, temptype;
            string tempid;
            int fine, space;

            while (getline(file, line))
            {
                vector<Books> borrowedBooks;
                stringstream ss(line);
                ss >> tempid >> tempusername >> password >> fine >> space >> temptype;
                string bookTitle;
                while (ss >> bookTitle)
                {
                    Books book = getBook(bookTitle);
                    if (!book.getTitle().empty())
                    {
                        borrowedBooks.push_back(book);
                    }
                    else
                    {
                        cout << "Warning: The book titled '" << bookTitle << "' could not be found." << endl;
                    }
                }
                if (temptype == "Faculty")
                {
                    Faculty faculty(tempusername, password);
                    faculty.setId(tempid);
                    faculty.setSpace(space);
                    faculty.setBooks(borrowedBooks);
                    faculties.push_back(faculty);
                }
            }
            file.close();
            for (Faculty &f : faculties)
            {
                if (f.getId() == ID)
                {
                    return f;
                }
            }
            cout << "Faculty not found" << endl;
        }
        else
        {
            cout << "Invalid type" << endl;
        }
    }
}
Faculty getFaculty(string username, string type)
{
    ifstream file(Accountpath);
    if (!file)
    {
        cerr << "Error opening file!" << endl;
    }
    else
    {
        if (type == "Faculty")
        {
            vector<Faculty> faculties;
            string line, tempusername, password, temptype;
            string id;
            int fine, space;

            while (getline(file, line))
            {
                vector<Books> borrowedBooks;
                stringstream ss(line);
                ss >> id >> tempusername >> password >> fine >> space >> temptype;
                string bookTitle;
                while (ss >> bookTitle)
                {
                    Books book = getBook(bookTitle);
                    if (!book.getTitle().empty())
                    {
                        borrowedBooks.push_back(book);
                    }
                    else
                    {
                        cout << "Warning: The book titled '" << bookTitle << "' could not be found." << endl;
                    }
                }
                if (type == "Faculty")
                {
                    Faculty faculty(tempusername, password);
                    faculty.setId(id);
                    faculty.setSpace(space);
                    faculty.setBooks(borrowedBooks);
                    faculties.push_back(faculty);
                }
            }
            file.close();
            for (Faculty &f : faculties)
            {
                if (f.getUsername() == username)
                {
                    return f;
                }
            }
            cout << "Faculty not found" << endl;
        }
        else
        {
            cout << "Invalid type" << endl;
        }
    }
    return {"", ""};
}

void Update_Student(Students updatedStudent)
{
    ifstream file(Accountpath);
    if (!file)
    {
        cerr << "Error opening file!" << endl;
        return;
    }

    vector<Students> students;
    vector<Faculty> faculties;
    string accountLine;
    bool found = false;

    while (getline(file, accountLine))
    {
        if (accountLine.empty())
            {continue;}
        stringstream ss(accountLine);
        string id, username, password, type;
        int fine, space;
        ss >> id >> username >> password >> fine >> space >> type;

        vector<Books> borrowedBooks;
        string bookTitle;
        while (ss >> bookTitle)
        {
            Books book = getBook(bookTitle);
            borrowedBooks.push_back(book);
        }
        if (type == "Students")
        {
            Students s(username, password);
            s.setId(id);
            s.IncreaseFine(fine);
            s.setSpace(space);
            s.setBooks(borrowedBooks);
            if (s.getUsername() == updatedStudent.getUsername())
            {
                s = updatedStudent;
                found = true;
            }
            students.push_back(s);
        }
        else if (type == "Faculty")
        {
            Faculty s(username, password);
            s.setId(id);
            s.setSpace(space);
            s.setBooks(borrowedBooks);
            faculties.push_back(s);
        }
    }
    file.close();

    if (!found)
    {
        cout << "Student not found, update failed." << endl;
        return;
    }

    ofstream outFile(Accountpath);
    if (!outFile)
    {
        cerr << "Error opening file for writing!" << endl;
        return;
    }

    for (Students &s : students)
    {
        outFile << s.getId() << " " << s.getUsername() << " " << s.getPassword()
                << " " << s.getFine() << " " << s.getSpace() << " " << s.getType() << " ";
        for (Books &book : s.getBorrowedBooks())
        {
            outFile << book.getTitle() << " ";
        }
        outFile << endl;
    }
    for (Faculty &s : faculties)
    {
        outFile << s.getId() << " " << s.getUsername() << " " << s.getPassword()
                << " " << s.getFine() << " " << s.getSpace() << " " << s.getType() << " ";
        for (Books &book : s.getBorrowedBooks())
        {
            outFile << book.getTitle() << " ";
        }
        outFile << endl;
    }
    outFile.close();
}

void UpdateFaculty(Faculty updatedfaculty)
{
    ifstream file(Accountpath);
    if (!file)
    {
        cerr << "Error opening file!" << endl;
        return;
    }

    vector<Faculty> students;
    string accountLine, booksLine;
    bool found = false;
    vector<Students> faculties;
    while (getline(file, accountLine))
    {
        if (accountLine.empty())
            {continue;}

        stringstream ss(accountLine);
        string id, username, password, type;
        int fine, space;
        ss >> id >> username >> password >> fine >> space >> type;

        vector<Books> borrowedBooks;
        
        string bookTitle;
        while (ss >> bookTitle)
        {
            Books book = getBook(bookTitle);
            borrowedBooks.push_back(book);
        }
        if (type == "Faculty")
        {
            Faculty s(username, password);
            s.setId(id);
            s.setSpace(space);
            s.setBooks(borrowedBooks);

            if (s.getUsername() == updatedfaculty.getUsername())
            {
                s = updatedfaculty;
                found = true;
            }

            students.push_back(s);
        }
        else
        {
            Students s(username, password);
            s.setId(id);
            s.IncreaseFine(fine);
            s.setSpace(space);
            s.setBooks(borrowedBooks);
            faculties.push_back(s);
        }
    }
    file.close();

    if (!found)
    {
        cout << "Faculty not found, update failed." << endl;
        return;
    }

    ofstream outFile(Accountpath);
    if (!outFile)
    {
        cerr << "Error opening file for writing!" << endl;
        return;
    }

    for (Faculty &s : students)
    {
        outFile << s.getId() << " " << s.getUsername() << " " << s.getPassword()
                << " " << s.getFine() << " " << s.getSpace() << " " << s.getType() << " ";
        for (Books &book : s.getBorrowedBooks())
        {
            outFile << book.getTitle() << " ";
        }
        outFile << endl;
    }
    for (Students &s : faculties)
    {
        outFile << s.getId() << " " << s.getUsername() << " " << s.getPassword()
                << " " << s.getFine() << " " << s.getSpace() << " " << s.getType() << " ";
        for (Books &book : s.getBorrowedBooks())
        {
            outFile << book.getTitle() << " ";
        }
        outFile << endl;
    }
    outFile.close();
}

void AddBooks(Books book)
{
    ifstream file(Bookpath);
    if (!file)
    {
        cerr << "Error opening file!" << endl;
        return;
    }
    vector<Books> books;
    string line, title, author, publisher, ISBN, status;
    time_t Date;
    while (getline(file, line))
    {
        stringstream ss(line);
        ss >> title >> author >> publisher >> Date >> ISBN >> status;
        Books b(title, author, publisher, Date, ISBN);
        b.setDate(Date);
        b.setStatus(status);
        books.push_back(b);
    }
    file.close();
    books.push_back(book);
    ofstream outFile(Bookpath);
    for (Books &b : books)
    {
        outFile << b.getTitle() << " " << b.getAuthor() << " " << b.getPublisher() << " "
                << b.getYear() << " " << b.ISBN << " " << b.getStatus() << endl;
    }
    outFile.close();
}

void RemoveBooks(Books book)
{
    ifstream file(Bookpath);
    if (!file)
    {
        cerr << "Error opening file!" << endl;
        return;
    }
    vector<Books> books;
    string line, title, author, publisher, ISBN, status;
    time_t Date;
    while (getline(file, line))
    {
        stringstream ss(line);
        ss >> title >> author >> publisher >> Date >> ISBN >> status;
        Books b(title, author, publisher, Date, ISBN);
        b.setDate(Date);
        b.setStatus(status);
        if (b.getTitle() != book.getTitle())
        {
            books.push_back(b);
        }
    }
    file.close();
    ofstream outFile(Bookpath);
    for (Books &b : books)
    {
        outFile << b.getTitle() << " " << b.getAuthor() << " " << b.getPublisher() << " "
                << b.getYear() << " " << b.ISBN << " " << b.getStatus() << endl;
    }
    outFile.close();
}

void UpdateBooks(Books Book)
{
    ifstream file(Bookpath);
    if (!file)
    {
        cerr << "Error opening file!" << endl;
        return;
    }
    vector<Books> books;
    string line, title, author, publisher, ISBN, status;
    time_t Date;
    while (getline(file, line))
    {   if(line.empty())
        {continue;}
        stringstream ss(line);
        ss >> title >> author >> publisher >> Date >> ISBN >> status;
        Books b(title, author, publisher, Date, ISBN);
        b.setDate(Date);
        b.setStatus(status);
        if (b.getTitle() == Book.getTitle())
        {
            b = Book;
        }
        books.push_back(b);
    }
    file.close();
    ofstream outFile(Bookpath);
    for (Books &b : books)
    {
        outFile << b.getTitle() << " " << b.getAuthor() << " " << b.getPublisher() << " "
                << b.getYear() << " " << b.ISBN << " " << b.getStatus() << endl;
    }
    outFile.close();
}

int CalculateFine(time_t Date)
{
    time_t now = time(nullptr);
    int minutes = 0;
    if(((now-Date)/60)>10){
        minutes = (((now - Date ) / 60)-10);
    }
    return minutes * 10;
}

void UpdateFine(Students &student)
{
    vector<Books> borrowedBooks = student.getBorrowedBooks();
    int totalFine = 0;
    for (Books &book : borrowedBooks)
    {
        totalFine += CalculateFine(book.getYear());
    }
    student.IncreaseFine(totalFine);
}

void DisplayStudent(Students student)
{
    cout << "Username: " << student.getUsername() << endl;
    cout << "Fine: " << student.getFine() << endl;
    cout << "Space: " << student.getSpace() << endl;
    cout << "Borrowed Books: " << endl;
    for (Books &book : student.getBorrowedBooks())
    {
        cout << book.getTitle() << endl;
    }
}

void DisplayFaculty(Faculty faculty)
{
    cout << "Username: " << faculty.getUsername() << endl;
    cout << "Fine: " << faculty.getFine() << endl;
    cout << "Space: " << faculty.getSpace() << endl;
    cout << "Borrowed Books: " << endl;
    for (Books book : faculty.getBorrowedBooks())
    {
        cout << book.getTitle() << endl;
    }
}

int Students::StudentsCount = 0;
int Faculty::FacultyCount = 0

    ;

void getStaticData()
{
    ifstream file(StaticDataPath);
    if (!file)
    {
        cerr << "Error opening file!" << endl;
        return;
    }
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        ss >> Students::StudentsCount >> Faculty::FacultyCount;
    }
    file.close();
}
void beginner_instructions()
{
    cout << endl
         << "Below are prompts that you need to give to navigate through this program" << endl
         << "When you are filling a prompt make sure its a single word, not something like\"wrong prompt\"." << endl;
    cout << "* \"sign-s\" -> To sign in as Student" << endl;
    cout << "* \"sign-a\" -> To sign in as manager(Librarian)" << endl;
    cout << "* \"sign-f\" -> To sign in as faculty" << endl;
    cout << "* \"exit\" -> To exit this program at any point" << endl;
    cout << "You can also do \"Ctrl + C\" to collapse the program at any point" << endl;
}

string SignInOrRegister()
{
    cout << "Please choose whether you want to sign in or register." << endl;
    cout << "1. sign-in" << endl;
    cout << "2. register" << endl;
    string choice;
    cin >> choice;
    return choice;
}

void StudentMenu(Students student)
{
    int choice;

    while (choice != 5)
    {
        cout << endl
             << "Please choose what you want to do" << endl;
        cout << "Please choose a number" << endl;
        cout << "1. Borrow a book" << endl;
        cout << "2. Return a book" << endl;
        cout << "3. Change password" << endl;
        cout << "4. Display your information" << endl;
        cout<< "5. Pay fine"<<endl;
        cout << "6. Exit" << endl
             << endl;
        cout << "Enter your choice" << endl;

        cin >> choice;
        if (choice == 1)
        {
            string title;
            cout << "Enter the title of the book you want to borrow" << endl;
            cin >> title;
            Books book = student.borrowBook(title);
            if (book.getTitle() != "")
            {
                student.addBook(book);
                Update_Student(student);
            }
            else
            {
                cout << "Book not found" << endl;
            }
        }
        else if (choice == 2)
        {
            string title;
            cout << "Enter the title of the book you want to return" << endl;
            cin >> title;
            Books book = student.returnBook(title);
            if (book.getTitle() != "")
            {
                student.RemoveBook(book);
                Update_Student(student);
            }
            else
            {
                cout << "Book not found" << endl;
            }
        }
        else if (choice == 3)
        {
            string password;
            cout << "Enter your new password" << endl;
            cin >> password;
            student.changePassword(password);
            Update_Student(student);
        }
        else if (choice == 4)
        {
            DisplayStudent(student);
        }
        else if (choice == 5)
        {
            cout<<"Enter the amount you want to pay"<<endl;
            int fine;
            cin>>fine;
            student.DecreaseFine(fine);
            Update_Student(student);
        }
        else if (choice == 6)
        {
            cout << "Exiting" << endl;
            break;
        }
        else
        {
            cout << "Invalid choice" << endl;
        }
    }
}

void DeleteAccount(const string &id)
{
    ifstream file(Accountpath);
    if (!file)
    {
        cerr << "Error opening file!" << endl;
        return;
    }
    if(id[id.size()-1]=='t'){
        Students::StudentsCount--;
        Students student= getStudentbyId(id,"Students");
        for(Books &book : student.getBorrowedBooks()){
            Books temp=student.returnBook(book.getTitle());
            student.RemoveBook(book);
        }
        Update_Student(student);
    }
    else{
        Faculty::FacultyCount--;
        Faculty faculty= getFacultybyID(id,"Faculty");
        for(Books &book : faculty.getBorrowedBooks()){
            faculty.RemoveBook(book);
            Books temp=faculty.returnBook(book.getTitle());
        }
        UpdateFaculty(faculty);
    }
    vector<string> updatedLines;
    string line;

    bool found = false;

    while (getline(file, line))
    {
        stringstream ss(line);

        string tempId;
        ss >> tempId;

        if (tempId != id)
        {
            updatedLines.push_back(line);
        }
        else
        {
            found = true;
        }
    }
    file.close();

    if (!found)
    {
        cout << "Account not found. Deletion failed." << endl;
        return;
    }

    ofstream outFile(Accountpath);
    if (!outFile)
    {
        cerr << "Error opening file for writing!" << endl;
        return;
    }

    for (const string &updatedLine : updatedLines)
    {
        outFile << updatedLine << endl; // Write back non-deleted accounts
    }

    outFile.close();
}
void FacultyMenu(Faculty faculty)
{
    int choice;

    while (choice != 5)
    {
        cout << endl
             << "Please choose what you want to do" << endl;
        cout << "Please choose a number" << endl;
        cout << "1. Borrow a book" << endl;
        cout << "2. Return a book" << endl;
        cout << "3. Change password" << endl;
        cout << "4. Display your information" << endl;
        cout << "5. Exit" << endl
             << endl;
        cout << "Enter your choice" << endl;

        cin >> choice;
        if (choice == 1)
        {
            string title;
            cout << "Enter the title of the book you want to borrow" << endl;
            cin >> title;
            Books book = faculty.borrowBook(title);
            if (book.getTitle() != "")
            {
                faculty.addBook(book);
                UpdateFaculty(faculty);
            }
            else
            {
                cout << "Book not found" << endl;
            }
        }
        else if (choice == 2)
        {
            string title;
            cout << "Enter the title of the book you want to return" << endl;
            cin >> title;
            Books book = faculty.returnBook(title);
            if (book.getTitle() != "")
            {
                faculty.RemoveBook(book);
                UpdateFaculty(faculty);
            }
            else
            {
                cout << "Book not found" << endl;
            }
        }
        else if (choice == 3)
        {
            string password;
            cout << "Enter your new password" << endl;
            cin >> password;
            faculty.changePassword(password);
            UpdateFaculty(faculty);
        }
        else if (choice == 4)
        {
            DisplayFaculty(faculty);
        }
        else if (choice == 5)
        {
            cout << "Exiting" << endl;
            break;
        }
        else
        {
            cout << "Invalid choice" << endl;
        }
    }
}

void UpdateAllAccounts()
{
    ifstream file(Accountpath);
    if (!file)
    {
        cerr << "Error opening file!" << endl;
        return;
    }

    string id, username, password, type;
    int fine, space;
    vector<Books> borrowedBooks;
 
    string line;    
    while (getline(file, line))
    {      stringstream ss(line);
        if(line.empty())
            {continue;}
        ss >> id >> username >> password >> fine >> space >> type;
        borrowedBooks.clear();
        string bookTitle;
        while (ss >> bookTitle && bookTitle != "")
        {
            Books book = getBook(bookTitle);
            if (!book.getTitle().empty())
            {
                borrowedBooks.push_back(book);
            }
        }
        if (type == "Students")
        {
            Students student(username, password);
            student.setId(id);
            student.IncreaseFine(fine);
            student.setSpace(space);
            student.setBooks(borrowedBooks);
            UpdateFine(student);
            Update_Student(student);
        }
        else if (type == "Faculty")
        {
            Faculty faculty(username, password);
            faculty.setId(id);
            faculty.setSpace(space);
            faculty.setBooks(borrowedBooks);
            UpdateFaculty(faculty);
        }
    }
    file.close();

}
void UpdateStaticData()
{
    ofstream file(StaticDataPath);
    if (!file)
    {
        cerr << "Error opening file!" << endl;
        return;
    }
    file << Students::StudentsCount << " " << Faculty::FacultyCount << endl;
    file.close();
}

void LibrarianMenu(){
        int choice;
    while(choice!=6){
        cout << endl
             << "Please choose what you want to do" << endl;
        cout << "Please choose a number" << endl;
        cout << "1. Add a book" << endl;
        cout << "2. Remove a book" << endl;
        cout << "3. Display all students" << endl;
        cout << "4. Display all faculties" << endl;
        cout << "5. Delete an account" << endl;
        cout << "6. Exit" << endl
             << endl;
        cout << "Enter your choice" << endl;
        cin >> choice;
        if (choice == 1)
        {
            Books newBook = addBooks();
            AddBooks(newBook);
        }
        else if (choice == 2)
        {
            string title;
            cout << "Enter the title of the book you want to remove" << endl;
            cin >> title;
            Books book = getBook(title);
            RemoveBooks(book);
        }
        else if (choice == 3)
        {
            ifstream file(Accountpath);
            if (!file)
            {
                cerr << "Error opening file!" << endl;
            }

            string line, id, username, password, type;
            int fine, space;
            vector<Books> borrowedBooks;
        while(getline(file,line)){
            stringstream ss(line);
            ss >> id >> username >> password >> fine >> space >> type;
            borrowedBooks.clear();
            string bookTitle;
            while(ss >> bookTitle && bookTitle != " "){
                Books book = getBook(bookTitle);
                if(!book.getTitle().empty()){
                    borrowedBooks.push_back(book);
                }
            }
            if(type == "Students"){
                Students student(username,password);
                student.setId(id);
                student.IncreaseFine(fine);
                student.setSpace(space);
                student.setBooks(borrowedBooks);
                DisplayStudent(student);
            }
        }
        file.close();
        }
        else if (choice == 4)
        {
            ifstream file(Accountpath);
            if (!file)
            {
                cerr << "Error opening file!" << endl;
            }

            string line, id, username, password, type;
            int fine, space;
            vector<Books> borrowedBooks;
        while(getline(file,line)){
            stringstream ss(line);
            ss >> id >> username >> password >> fine >> space >> type;
            borrowedBooks.clear();
            string bookTitle;
            while(ss >> bookTitle && bookTitle != " "){
                Books book = getBook(bookTitle);
                if(!book.getTitle().empty()){
                    borrowedBooks.push_back(book);
                }
            }
            if(type == "Faculty"){
                Faculty faculty(username,password);
                faculty.setId(id);
                faculty.setSpace(space);
                faculty.setBooks(borrowedBooks);
                DisplayFaculty(faculty);
            }

        }
        file.close();
        }
        else if (choice == 5)
        {
            string id;
            cout << "Enter the id of the account you want to delete" << endl;
            cin >> id;
            DeleteAccount(id);
        }
        else if (choice == 6)
        {
            cout << "Exiting" << endl;
        }
        else
        {
            cout << "Invalid choice" << endl;
        }
    }
}


int main()
{
    // Books newBook = addBooks();
    // newBook.DisplayBook();
    getStaticData();
    UpdateAllAccounts();
    cout << "Welcome to the Library of Eternity" << endl;

    string prompt;

    while (prompt != "exit")
    {
        beginner_instructions();
        cout << "Enter your prompt" << endl;
        cin >> prompt;

        if (prompt == "sign-s")
        {
            string choice = SignInOrRegister();
            string username, password;
            if (choice == "sign-in")
            {
                cout << "Enter your username" << endl;
                cin >> username;
                cout << "Enter your password" << endl;
                cin >> password;
                Students student("", "");
                student = getStudent(username, "Students");
                if (student.getUsername() == username)
                {
                    if (student.getPassword() == password)
                    {
                        cout << "Welcome " << student.getUsername() << endl;
                        StudentMenu(student);
                    }
                    else
                    {
                        cout << "Invalid password" << endl;
                    }
                }
                else
                {
                    cout << "Student not found" << endl;
                }
            }
            else if (choice == "register")
            {
                CreateAccount();
                cout << "Enter your username again please" << endl;
                cin >> username;
                StudentMenu(getStudent(username, "Students"));
            }
            else
            {
                cout << "Invalid choice" << endl;
            }
        }
        else if (prompt == "sign-f")
        {
            string choice = SignInOrRegister();
            string username, password;
            if (choice == "sign-in")
            {
                cout << "Enter your username" << endl;
                cin >> username;
                cout << "Enter your password" << endl;
                cin >> password;
                Faculty faculty = getFaculty(username, "Faculty");
                if (faculty.getUsername() == username)
                {
                    if (faculty.getPassword() == password)
                    {
                        cout << "Welcome " << faculty.getUsername() << endl;
                        DisplayFaculty(faculty);
                        FacultyMenu(faculty);
                    }
                    else
                    {
                        cout << "Invalid password" << endl;
                    }
                }
                else
                { 
                }
            }
            else if (choice == "register")
            {

                CreateAccount();
                cout << "Enter your username again please" << endl;
                cin >> username;
                FacultyMenu(getFaculty(username, "Faculty"));
            }
            else
            {
                cout << "Invalid choice" << endl;
            }
        }
        else if (prompt == "sign-a")
        {
            string username, password;
            cout << "Enter your username" << endl;
            cin >> username;
            cout << "Enter your password" << endl;
            cin >> password;
            if (username == "Neon" && password == "Diff")
            {
                cout << "Welcome Librarian" << endl;
                LibrarianMenu();
            }
            else
            {
                cout << "Invalid username or password" << endl;
            }
        }
        else if(prompt=="exit"){
            cout<<"Bye"<<endl;
            break;
        }
        else{
            cout<<"Invalid prompt"<<endl;
        }}
    UpdateStaticData();
    UpdateAllAccounts();
    return 0;
}


