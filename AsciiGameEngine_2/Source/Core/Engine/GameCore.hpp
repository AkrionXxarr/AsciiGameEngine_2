#pragma once

class Renderer;
class Object;

class GameCore
{
public:
    GameCore();
    virtual ~GameCore();

    virtual void Initialize() { }

    void Update(float deltaTime);
    void Draw(Renderer* renderer);

    void AddObjectToRoot(Object* obj);

private:
    Object* root = nullptr;
};