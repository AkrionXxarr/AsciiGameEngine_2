#include "GameCore.hpp"
#include "Core\Engine\Renderer.hpp"
#include "Core\Object\Object.hpp"

GameCore::GameCore()
{
    root = new Object;
}

GameCore::~GameCore()
{
    if (root != nullptr)
    {
        root->Destroy();
        delete root;
    }
}

void GameCore::Update(float deltaTime)
{
    root->UpdateAll(deltaTime);
}

void GameCore::Draw(Renderer* renderer)
{
    renderer->Draw(root);
}

void GameCore::AddObjectToRoot(Object* obj)
{
    root->AddChild(obj);
}