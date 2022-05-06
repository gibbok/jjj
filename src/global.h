#pragma once
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <curses.h>

struct DirItem
{
    char name[1024];
    int is_dir;
    // FIXME add path of the file
};

struct AppState
{
    char cwd[256];
    struct DirItem dir_entries[500]; // FIXME: must use dynamic allocation
    int dir_entries_total;
    int user_highlight;
    int user_choice;
    int user_key_pressed;
};

#define WIDTH 100 // TODO get the terminal size here
#define HEIGHT 100

#define RENDER_START_X 0
#define RENDER_START_Y 0

#define KEY_J 106
#define KEY_K 107
#define KEY_L 108
#define KEY_H 104
#define KEY_Q 113
#define KEY_ESC 27
#define KEY_SPACEBAR 32

WINDOW *menu_win;
