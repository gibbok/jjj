#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include "header/global.h"

// Print to screen results
void render_cwd(struct AppState *state)
{
    printw("%s\n", state->cwd);
}

void render_dir_items_total(struct AppState *state)
{
    printw("Total: %i\n", state->dir_entries_total);
}

void print_dir_items(struct AppState *state)
{
    int i;
    for (i = 0; i < state->dir_entries_total; ++i)
    {
        struct DirItem item = state->dir_entries[i];
        if (item.is_dir == 1)
            printw("%s/\n", item.name);
        else
            printw("%s\n", item.name);
    }
}

void render_screen(struct AppState *state)
{
    render_cwd(state);
    render_dir_items_total(state);
    print_dir_items(state);
    refresh();
};

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

void render_window()
{
    menu_win = newwin(HEIGHT, WIDTH, starty, startx);
    keypad(menu_win, TRUE);
    refresh();
}

void render_menu(WINDOW *menu_win, int highlight)
{
    int x, y, i;

    x = 2;
    y = 2;
    box(menu_win, 0, 0);
    for (i = 0; i < n_choices; ++i)
    {
        if (highlight == i + 1) /* High light the present choice */
        {
            wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, y, x, "%s", choices[i]);
            wattroff(menu_win, A_REVERSE);
        }
        else
            mvwprintw(menu_win, y, x, "%s", choices[i]);
        ++y;
    }
    wrefresh(menu_win);
}

void detect_mouse()
{
    while (1)
    {
        c = wgetch(menu_win);
        switch (c)
        {
        case KEY_UP:
            if (highlight == 1)
                highlight = n_choices;
            else
                --highlight;
            break;
        case KEY_DOWN:
            if (highlight == n_choices)
                highlight = 1;
            else
                ++highlight;
            break;
        case 10:
            choice = highlight;
            break;
        default:
            refresh();
            break;
        }
        render_menu(menu_win, highlight);
        if (choice != 0) /* User did a choice come out of the infinite loop */
            break;
    }
    mvprintw(23, 0, "You chose choice %d with choice string %s\n", choice, choices[choice - 1]);
    clrtoeol();
    refresh();
}