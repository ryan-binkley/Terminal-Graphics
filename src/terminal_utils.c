#include <unistd.h>
#include <sys/ioctl.h>
#include "errors.h"

void getTerminalSize(int* width, int* height)
{
    struct winsize window_size;

    if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &window_size))
    {
        killProgram("ioctl");
    }

    *width = window_size.ws_col;
    *height = window_size.ws_row;
}