
//  errors.h
//  Exceptions

#ifndef Exceptions_exception_h
#define Exceptions_exception_h

#include <iostream>
#include <cstring>
#include <exception>

using namespace std;


class out_of_screen : public exception
{
public:
    out_of_screen(string message) : exception(c.str(message)) {}
};


class bad_init : public exception
{
public:
    bad_init(string message){ cout << "Bad_init: " << message << endl;}
};


#endif
