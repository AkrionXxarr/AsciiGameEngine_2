#pragma once

#include "GameCore.hpp"

class TestGame : public GameCore
{
public:
    TestGame();
    virtual ~TestGame();

    virtual void Initialize();
};