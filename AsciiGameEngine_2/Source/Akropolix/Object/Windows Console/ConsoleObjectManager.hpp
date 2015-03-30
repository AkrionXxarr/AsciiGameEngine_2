/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#include <vector>

#include "Akropolix\Object\Interface\IObjectManager.hpp"

namespace Akropolix
{
    namespace Input
    {
        namespace WinConsole
        {
            class ConsoleInputExt;
        }
    }

    namespace Object
    {
        namespace WinConsole
        {
            class ConsoleObject;

            class ConsoleObjectManager : public Object::Interface::IObjectManager
            {
            public:
                ConsoleObjectManager();
                ~ConsoleObjectManager();

                virtual void Update(float deltaTime);
                virtual void Draw(Render::Interface::IRenderContext& renderContext);

                void Input(Input::WinConsole::ConsoleInputExt& input);

                virtual void AddObject(Object::Interface::IObject* object);
                virtual Object::Interface::IObject* RemoveObject(unsigned int ID);

            private:
                // Very basic object structure
                std::vector<ConsoleObject*> objects;
            };
        };
    };
};