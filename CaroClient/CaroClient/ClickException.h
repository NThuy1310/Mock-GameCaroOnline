#pragma once
#include <exception>
using namespace std;

class ClickException : public exception
{
private:

public:
    const char* what() const throw()
    {
        return "Click Invalid !";
    }
};