#include "GameCore.hpp"
#include "Core\Draw\Renderer.hpp"
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
    root->UpdateChildren(deltaTime);
}

void GameCore::Draw(Renderer* renderer)
{
    renderer->Draw(root);
}

void GameCore::AddObjectToRoot(Object* obj)
{
    root->AddChild(obj);
}