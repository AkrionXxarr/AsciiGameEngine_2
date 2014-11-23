#include "Core\Display\ConsoleDefines.hpp"
#include "TestGame.hpp"
#include "TestObject.hpp"

TestGame::TestGame()
{

}

TestGame::~TestGame()
{

}

void TestGame::Initialize()
{
    TestObject* obj = new TestObject(1, f_halfGreen | b_halfRed, 10, 15);
    TestObject* obj2 = new TestObject(2, f_fullCyan, -10, 15);
    TestObject* obj3 = new TestObject(0, f_black | b_white, -10, -15);

    //obj->position = Vector2f(5, 5);
    //obj2->position = Vector2f(8, 8);
    //obj3->position = Vector2f(3, 3);

    AddObjectToRoot(obj);
    AddObjectToRoot(obj2);
    AddObjectToRoot(obj3);
}