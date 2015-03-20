/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#pragma once

#include "Input\Windows Input\ConsoleInput.hpp"

//////////////////////////////////////////////////////////////////////////////
// An extension on the base functionality of ConsoleInput
//
class ConsoleInputExt : public ConsoleInput
{
public:
    /* Construct & Destruct */
    ConsoleInputExt(unsigned int inputBufferSize);
    virtual ~ConsoleInputExt();

    virtual void Tick();

    char GetCharacter();

    KEYBOARD GetMostRecentKey();
    MOUSE_BUTTON GetMostRecentMouseButton();

    bool GetAnyKeyUp();
    bool GetAnyKeyDown();   
    
    bool GetAnyMouseUp();
    bool GetAnyMouseDown();
    
protected:
    KEYBOARD mostRecentKey;
    MOUSE_BUTTON mostRecentMouseButton;

    bool capsLock, scrollLock, numLock;
};