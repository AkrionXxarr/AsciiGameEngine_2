#include "TestGame.hpp"
#include "TestComponent.hpp"

#include "Core\Display\ConsoleDefines.hpp"
#include "Core\Object\Object.hpp"

TestGame::TestGame()
{

}

TestGame::~TestGame()
{
}

void TestGame::Initialize()
{
    Object* obj1 = new Object;
    Object* obj2 = new Object;
    Object* obj3 = new Object;

    obj1->AddComponent(new TestComponent(1, f_halfGreen | b_halfRed, 10, 15));
    obj2->AddComponent(new TestComponent(2, f_fullCyan, -10, 15));
    obj3->AddComponent(new TestComponent(0, f_black | b_white, -10, -15));

    AddObjectToRoot(obj1);
    AddObjectToRoot(obj2);
    AddObjectToRoot(obj3);
}