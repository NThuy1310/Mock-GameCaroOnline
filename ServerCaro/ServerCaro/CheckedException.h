#pragma once
#include <exception>
using namespace std;

class CheckedException : public exception
{
private:

public:
    const char* what() const throw()
    {
        return "Checked Invalid !";
    }
};