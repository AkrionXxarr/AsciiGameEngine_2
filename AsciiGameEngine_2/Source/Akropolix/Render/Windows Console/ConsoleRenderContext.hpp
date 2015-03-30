/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#pragma once

#include <Windows.h>
#include <memory>

#include "Akropolix\Render\Interface\IRenderContext.hpp"

class ConsoleBuffer;

class ConsoleRenderContext : public IRenderContext
{
public:
    ConsoleRenderContext();
    ~ConsoleRenderContext();

    void Initialize(std::shared_ptr<ConsoleBuffer> buffer);

    void Clear();

    void DrawPoint(POINT& pos, CHAR_INFO& ci);

private:
    std::shared_ptr<ConsoleBuffer> buffer;
};