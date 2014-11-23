#include <iostream>

#include "Core\Engine\MainEngine.hpp"
#include "Test\TestGame.hpp"

int main(int argc, const char* argv[])
{
    MainEngine engine(new TestGame, 80, 25);

    engine.Start();

    system("pause");

    return 0;
}