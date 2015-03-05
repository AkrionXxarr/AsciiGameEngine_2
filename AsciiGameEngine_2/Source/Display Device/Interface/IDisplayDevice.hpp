/*
* Copyright (c) 2015, Stephen Bloomquist
* All rights reserved.
*/

#pragma once
#include <memory>

template <class T>
struct DisplayBuffer
{
    unsigned int width, height;
    T* buffer;
};

/*
* An interface that provides methods and variables that all display devices
* must have in order to achieve the goal of pushing a buffer to a screen.
*/
template<class BufferType>
class IDisplayDevice
{
public:
    IDisplayDevice() { }
    virtual ~IDisplayDevice() { }

    virtual void Display() = 0;

protected:
    std::shared_ptr<DisplayBuffer<BufferType> > displayBuffer;

private:
    // The display device shouldn't be copied anywhere
    IDisplayDevice(const IDisplayDevice& other);
    void operator = (const IDisplayDevice& other);
};