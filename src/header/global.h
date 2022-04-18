#pragma once
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <curses.h>
#include "global.h"

struct DirItem
{
    char name[1024];
    int is_dir;
};

struct AppState
{
    char cwd[256];
    struct DirItem dir_entries[500]; // FIXME: must use dynamic allocation
    int dir_entries_total;
};

#define WIDTH 30
#define HEIGHT 10

WINDOW *menu_win;

int highlight = 1;
int choice = 0;
int c;
int startx = 0;
int starty = 0;
