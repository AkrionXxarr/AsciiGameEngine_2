/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#include "Input\Windows Input\ConsoleInput.hpp"
#include "Utility\Math\Vector2f.hpp"

ConsoleInput::ConsoleInput(POINT mouseFreezePos)
{
    mouseDelta = new Vector2f();
    this->mouseFreezePos = mouseFreezePos;
    SetCursorPos(mouseFreezePos.x, mouseFreezePos.y);
}

ConsoleInput::~ConsoleInput()
{
    if (mouseDelta)
        delete mouseDelta;
}

void ConsoleInput::Tick()
{
    POINT curMousePos;
    
    GetCursorPos(&curMousePos);

    mouseDelta->x = float(curMousePos.x - mouseFreezePos.x);
    mouseDelta->y = float(curMousePos.y - mouseFreezePos.y);

    SetCursorPos(mouseFreezePos.x, mouseFreezePos.y);
}

Vector2f ConsoleInput::GetMouseDelta()
{
    return Vector2f(mouseDelta->x, mouseDelta->y);
}
