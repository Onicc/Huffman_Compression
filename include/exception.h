#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <iostream>
#include <exception>
#include <string>

using namespace std;

class MyException : public exception {
    public:
        MyException(string str) : message("Error: " + str) {}
        ~MyException() throw () {}

        virtual const char* what() const throw () {
            return message.c_str();
        }

    private:
        string message;
};

#endif