/*
* Copyright(c) 2015, Stephen Bloomquist
* All rights reserved.
*/

namespace aki
{
    namespace display
    {
        namespace I
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
