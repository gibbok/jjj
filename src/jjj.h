#pragma once
#include <dirent.h>

struct DirItem
{
    char name[1024];
    int is_dir;
};

struct AppState
{
    char cwd[256];
    struct DirItem dir_entries[500];
};
