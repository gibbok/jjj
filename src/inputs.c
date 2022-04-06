#include "header/global.h"

void detect_inputs()
{
    int ch;
    ch = getch();
    if (ch == KEY_LEFT)
        printw("Left arrow is pressed\n");
}