/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#include <Windows.h>

#include <fstream>
#include <sstream>
#include <iomanip>

#include "Utility\Logging\Log.hpp"

using namespace std;

void AddToLog(string msg, string fileName)
{
    ofstream fs;
    fs.open(fileName, ofstream::out | ofstream::app);

    if (fs.is_open())
    {
        fs << msg;
        fs << "\n";
    }

    fs.close();
}

void ClearLogFile(string fileName)
{
    ofstream fs;
    fs.open(fileName, ofstream::out | ofstream::trunc);
    fs.close();
}

void LogMessage(string msg, string fileName)
{
    AddToLog(msg, fileName);
}

void LogWarning(string msg, string fileName)
{
    string str = "[Warning] ";
    str.append(msg);
    AddToLog(str, fileName);
}

void LogError(string msg, string fileName)
{
    string str = "<ERROR> ";
    str.append(msg);
    AddToLog(str, fileName);
}

void LogWindowsError(string fileName)
{
    stringstream sstream;
    DWORD err = GetLastError();

    sstream << "Windows error code: 0x";
    sstream << std::setfill('0') << setw(4) << std::hex << std::uppercase << err;

    LogError(sstream.str(), fileName);
}