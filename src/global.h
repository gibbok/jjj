#pragma once
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <curses.h>
#include <limits.h>

struct DirItem
{
    char name[NAME_MAX];
    int is_dir;
};

struct AppState
{
    char cwd[PATH_MAX];
    struct DirItem dir_entries[500]; // FIXME: must use dynamic allocation
    int dir_entries_total;
    int user_highlight;
    int user_key_pressed;
};

#define RENDER_START_X 0
#define RENDER_START_Y 0

#define KEY_J 106
#define KEY_K 107
#define KEY_L 108
#define KEY_H 104
#define KEY_Q 113
#define KEY_ESC 27
#define KEY_RETURN 10
#define KEY_SPACEBAR 32

WINDOW *menu_win;
