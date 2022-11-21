#pragma once
#include <exception>
using namespace std;

class CommandException : public exception
{
private:

public:
    const char* what() const throw()
    {
        return "Index Invalid !!!";
    }
};