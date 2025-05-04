cmake_minimum_required(VERSION 3.26)
project(Scnu_Lab_Library)

set(CMAKE_CXX_STANDARD 17)

add_executable(Scnu_Lab_Library 
    main.cpp 
    Book.cpp 
    Book.h 
    Reader.cpp 
    Reader.h 
    LibrarySystem.cpp 
    LibrarySystem.h
)
