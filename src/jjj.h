#pragma once
#include <dirent.h>
#include <stdbool.h>

struct direntry
{
    char name[1024];
    bool is_dir;
};

struct appstate
{
    char cwd[256];
    struct dirent dir_entries;
};
