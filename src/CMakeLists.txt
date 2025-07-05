cmake_minimum_required(VERSION 3.28)
project(untitled1)

set(CMAKE_CXX_STANDARD 17)

add_executable(untitled1 main.cpp
        User.cpp
        User.h
        Account.cpp
        Account.h
        Books.cpp
        Books.h
        Students.cpp
        Students.h
        Faculty.cpp
        Faculty.h
        Librarian.cpp
        Librarian.h
)
