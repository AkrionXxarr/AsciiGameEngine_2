/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#include <vector>

#include "Akropolix\Object\Interface\IObjectManager.hpp"

namespace aki
{
    namespace input
    {
        namespace wincon
        {
            class ConsoleInputExt;
        }
    }

    namespace object
    {
        namespace wincon
        {
            class ConsoleObject;

            class ConsoleObjectManager : public object::I::IObjectManager
            {
            public:
                ConsoleObjectManager();
                ~ConsoleObjectManager();

                virtual void Update(float deltaTime);
                virtual void Draw(render::I::IRenderContext& renderContext);

                void Input(input::wincon::ConsoleInputExt& input);

                virtual void AddObject(object::I::IObject* object);
                virtual object::I::IObject* RemoveObject(unsigned int ID);

            private:
                // Very basic object structure
                std::vector<ConsoleObject*> objects;
            };
        };
    };
};