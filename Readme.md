<h1>LMS(Library Management System)</h1>
<h2>Overview</h2>
LMS (Library Management System) is a C++ program that  allows students, faculty, and librarians to manage books in a library.
Users can:

* View available books
* Borrow and return books
* Track issued books
* Maintain a history of borrowed books

<h2>Installation and Running Instructions </h2>

Before building the system you need to change the base path in the main.cpp and Account.cpp file to the path in which you have placed this project directory.

Make sure that you have cmake installed.

Check whether you have installed cmake or not.
<code> cmake --version</code>

If you have cmake installed then put the following commands in your cmd if you are using windows.

<code> cd src </code>

<code>mkdir build & cd build</code>

<code>cmake .. -G "MinGW Makefiles" </code> if you are using MinGW for your cpp compiler

<code>cmake --build . </code>

<code> ./untitled1.exe </code>

