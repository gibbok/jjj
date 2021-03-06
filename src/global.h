#pragma once

#define _GNU_SOURCE

#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>

#include <ncurses.h>

#define DEBUG_MODE 0
#define APP_VERSION "1.0.1"
#define RENDER_AT_WINDOW_POSITION_ROWS 0
#define RENDER_AT_WINDOW_POSITION_COLS 0
#define WINDOW_SAFE_MARGIN_ROWS 5
#define WINDOW_SAFE_MARGIN_COLS 2

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
    bool is_dir;
};

struct app_state
{
    char cwd[FILENAME_MAX];
    struct dir_item *dir_entries;
    int dir_entries_total;
    int user_highlight;
    int user_key_pressed;
    int window_rows_scroll;
    int window_rows;
    int window_cols;
};
