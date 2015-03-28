/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#pragma once

#include <string>

class ErrorHandler
{
public:
    ErrorHandler() { }
    ~ErrorHandler() { }

    static ErrorHandler* const Get();

    void WindowsError();
    void GeneralError(std::string msg);

private:
    std::string fileName;
};