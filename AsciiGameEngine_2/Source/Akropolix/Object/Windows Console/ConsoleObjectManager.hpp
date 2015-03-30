/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#include <vector>

#include "Akropolix\Object\Interface\IObjectManager.hpp"

namespace Akropolix
{
    class ConsoleInputExt;
    class ConsoleObject;

    class ConsoleObjectManager : public IObjectManager
    {
    public:
        ConsoleObjectManager();
        ~ConsoleObjectManager();

        virtual void Update(float deltaTime);
        virtual void Draw(IRenderContext& renderContext);

        void Input(ConsoleInputExt& input);

        virtual void AddObject(IObject* object);
        virtual IObject* RemoveObject(unsigned int ID);

    private:
        // Very basic object structure
        std::vector<ConsoleObject*> objects;
    };
};