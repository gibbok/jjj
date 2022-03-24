#pragma once
#include <dirent.h>
struct appstate
{
    char cwd[256];
    struct dirent dir_entries;
};
