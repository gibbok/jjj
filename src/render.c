#pragma once
#include "global.h"

void render_window()
{
    menu_win = newwin(0, 0, RENDER_START_Y, RENDER_START_X);
    keypad(menu_win, TRUE);
    refresh();
}

void render_active_item(struct AppState *state)
{
    printf("%s/%s", state->cwd, state->dir_entries[state->user_highlight].name);
}

void render_item(WINDOW *menu_win, int y, int x, char *name, bool is_dir, bool is_active)
{
    int style = is_active == true ? A_REVERSE : A_NORMAL;
    char *dir_indicator = is_dir == true ? "/" : "";

    wattron(menu_win, style);
    mvwprintw(menu_win, y, x, "%s%s", name, dir_indicator);
    wattroff(menu_win, style);
}

void render(WINDOW *menu_win, struct AppState *state)
{
    int x, y, i;

    x = RENDER_START_X;
    y = RENDER_START_Y + 1;

    mvwprintw(menu_win, RENDER_START_Y, x, "%s", state->cwd);
    // debug only
    mvwprintw(menu_win, RENDER_START_Y + 20, x, "user_highlight %d\n", state->user_highlight);
    mvwprintw(menu_win, RENDER_START_Y + 21, x, "user_key_pressed %d\n", state->user_key_pressed);
    mvwprintw(menu_win, RENDER_START_Y + 23, x, "cwd %s\n", state->cwd);
    mvwprintw(menu_win, RENDER_START_Y + 25, x, "dir_entries_total %d\n", state->dir_entries_total);

    for (i = 0; i <= state->dir_entries_total; ++i)
    {
        if (state->user_highlight == i) /* High light the present choice */
        {
            render_item(menu_win, y, x, state->dir_entries[i].name, state->dir_entries[i].is_dir, true);
        }
        else
        {
            render_item(menu_win, y, x, state->dir_entries[i].name, state->dir_entries[i].is_dir, false);
        }
        ++y;
    }
    wrefresh(menu_win);
}
