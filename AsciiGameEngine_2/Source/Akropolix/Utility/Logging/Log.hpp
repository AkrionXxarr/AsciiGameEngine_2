/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#pragma once

#include <string>

namespace Akropolix
{
    namespace Log
    {
        void ClearLogFile(std::string fileName);

        void LogMessage(std::string msg, std::string fileName);
        void LogWarning(std::string msg, std::string fileName);
        void LogError(std::string msg, std::string fileName);

        void LogWindowsError(std::string fileName);
    };
};