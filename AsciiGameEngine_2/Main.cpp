#include <iostream>

#include "MainEngine.hpp"
#include "TestGame.hpp"

int main(int argc, const char* argv[])
{

    system("pause");
    return 0;

    MainEngine engine(new TestGame, 80, 25);

    engine.Start();

    system("pause");

    return 0;
}