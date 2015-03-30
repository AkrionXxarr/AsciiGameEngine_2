/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

namespace Akropolix
{
    namespace DisplayDevice
    {
        namespace Interface
        {
            class IDisplayDevice
            {
            public:
                IDisplayDevice() { }
                virtual ~IDisplayDevice() { }

                virtual void Display() = 0;

                virtual bool HasFocus() = 0;

            private:
                IDisplayDevice(const IDisplayDevice& other);
                void operator= (const IDisplayDevice& other);
            };
        };
    };
};
