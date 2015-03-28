#include <Windows.h>
#include <sstream>

#include "Utility\Logging\Log.hpp"
#include "Utility\Error Handling\Windows\ErrorHandler.hpp"

using namespace std;




void ErrorHandler::WindowsError()
{
    stringstream sstream;
    DWORD err = GetLastError();

    sstream << "Windows error code: ";
    sstream << err;

    LogError(sstream.str() , fileName);
}

void ErrorHandler::GeneralError(string msg)
{
    LogError(msg, fileName);
}