#pragma once
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <curses.h>
#include <limits.h>
#include <pthread.h>

#define RENDER_START_X 0
#define RENDER_START_Y 0

#define KEY_J 106
#define KEY_K 107
#define KEY_L 108
#define KEY_H 104
#define KEY_Q 113
#define KEY_R 114
#define KEY_ESC 27
#define KEY_RETURN 10
#define KEY_SPACEBAR 32

struct dir_item
{
    char name[NAME_MAX];
    int is_dir;
};

struct app_state
{
    char cwd[PATH_MAX];
    struct dir_item *dir_entries;
    int dir_entries_total;
    int user_highlight;
    int user_key_pressed;
};

WINDOW *menu_win;
