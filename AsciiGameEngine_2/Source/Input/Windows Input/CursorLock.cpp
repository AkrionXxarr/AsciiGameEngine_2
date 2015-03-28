/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#include "Input\Windows Input\ConsoleInputExt.hpp"

CursorLock::CursorLock()
{
    delta = { 0, 0 };
    center = { 0, 0 };
    running = false;

    InitializeCriticalSection(&pointCritical);
    InitializeCriticalSection(&runCritical);
    handle = INVALID_HANDLE_VALUE;
}

CursorLock::~CursorLock()
{
    DeleteCriticalSection(&pointCritical);
    DeleteCriticalSection(&runCritical);
    handle = INVALID_HANDLE_VALUE;
}

unsigned int __stdcall CursorLock::Run(void* params)
{
    POINT p;
    CursorLock* cl = (CursorLock*)params;

    for (;;)
    {
        GetCursorPos(&p);

        EnterCriticalSection(&cl->pointCritical);
        cl->delta.x += p.x - cl->center.x;
        cl->delta.y += p.y - cl->center.y;

        SetCursorPos(cl->center.x, cl->center.y);
        LeaveCriticalSection(&cl->pointCritical);

        EnterCriticalSection(&cl->runCritical);
        if (!cl->running) break; // Kill the loop
        LeaveCriticalSection(&cl->runCritical);
    }
    LeaveCriticalSection(&cl->runCritical);

    _endthreadex(0);
    return 0;
}

void CursorLock::Start(POINT c)
{
    EnterCriticalSection(&runCritical);
    if (!running)
    {
        center = c;
        running = true;
        handle = HANDLE(_beginthreadex(0, 0, &CursorLock::Run, (void*)this, 0, 0));
    }
    LeaveCriticalSection(&runCritical);
}

void CursorLock::Stop()
{
    EnterCriticalSection(&runCritical);
    if (running)
    {
        running = false;
        handle = INVALID_HANDLE_VALUE;
    }
    LeaveCriticalSection(&runCritical);
}

POINT CursorLock::GetDelta()
{
    EnterCriticalSection(&pointCritical);
    POINT p;
    p.x = delta.x;
    p.y = delta.y;
    delta.x = 0;
    delta.y = 0;
    LeaveCriticalSection(&pointCritical);

    return p;
}