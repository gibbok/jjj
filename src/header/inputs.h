#pragma once
#include "global.h"

#define WIDTH 30
#define HEIGHT 10

WINDOW *menu_win;

int highlight = 1;
int choice = 0;
int c;
int startx = 0;
int starty = 0;

char *choices[] = {
    "Choice 1",
    "Choice 2",
    "Choice 3",
    "Choice 4",
    "Exit",
};

int n_choices = sizeof(choices) / sizeof(char *);