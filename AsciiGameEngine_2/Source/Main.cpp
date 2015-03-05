#include <iostream>

#include "Display Device\Windows Console\Console.hpp"
#include "Display Device\Windows Console\ConsoleDefines.hpp"

int main(int argc, const char* argv[])
{
    Console console;
    std::shared_ptr<ConsoleBuffer> consoleBuffer(new ConsoleBuffer(70, 30));

    console.CreateDevice(consoleBuffer, 25, FONT_8x8);
    console.ClearBuffer();

    consoleBuffer->useDrawRect = false;

    unsigned int X = consoleBuffer->GetSizeAsCoord().X;
    unsigned int Y = consoleBuffer->GetSizeAsCoord().Y;

    char c = ' ';
    unsigned short color = 0;
    for (unsigned int row = 0; row < Y; row++)
    {
        for (unsigned int col = 0; col < X; col++)
        {
            if ((row > 4 && row < Y - 5) && (col > 4 && col < X - 5))
            {
                c = char(139);
                color = b_halfYellow | f_fullYellow;
            }
            else
            {
                c = 'Z';
                color = b_halfPurple | f_fullBlue;
            }
            CHAR_INFO ci = { c, color };
            consoleBuffer->Put(col, row, ci);
        }
    }

    console.Display();
    console.ClearBuffer();

    system("pause");

    consoleBuffer->drawRect = { 5, 5, 64, 24 };
    consoleBuffer->useDrawRect = true;

    console.Display();

    system("pause");

    return 0;
}