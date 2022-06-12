/*  Render the application state into the terminal. */

#pragma once

#include "global.h"

WINDOW *render_window()
{
    WINDOW *main_window = newwin(0, 0, RENDER_AT_WINDOW_POSITION_Y, RENDER_AT_WINDOW_POSITION_X);
    keypad(main_window, TRUE);
    refresh();
    return main_window;
}

void render_active_item(struct app_state *state)
{
    printf("%s/%s", state->cwd, state->dir_entries[state->user_highlight].name);
}

void render_item(WINDOW *main_window, int y, int x, char *name, bool is_dir, bool is_active)
{
    int style = is_active == true ? A_REVERSE : A_NORMAL;
    char *dir_indicator = is_dir == true ? "/" : "";

    wattron(main_window, style);
    mvwprintw(main_window, y, x, "%s%s", name, dir_indicator);
    wattroff(main_window, style);
}

void render(WINDOW *main_window, struct app_state *state)
{
    int x, y, i;

    x = RENDER_AT_WINDOW_POSITION_X;
    y = RENDER_AT_WINDOW_POSITION_Y + 1;

    mvwprintw(main_window, RENDER_AT_WINDOW_POSITION_Y, x, "%s", state->cwd);

    if (DEBUG_MODE == 1)
    {
        mvwprintw(main_window, RENDER_AT_WINDOW_POSITION_Y + 20, x, "user_highlight %d\n", state->user_highlight);
        mvwprintw(main_window, RENDER_AT_WINDOW_POSITION_Y + 21, x, "user_key_pressed %d\n", state->user_key_pressed);
        mvwprintw(main_window, RENDER_AT_WINDOW_POSITION_Y + 23, x, "cwd %s\n", state->cwd);
        mvwprintw(main_window, RENDER_AT_WINDOW_POSITION_Y + 25, x, "dir_entries_total %d\n", state->dir_entries_total);
    }

    for (i = 0; i <= state->dir_entries_total; ++i)
    {
        if (state->user_highlight == i)
        {
            /* High light the present choice */
            render_item(main_window, y, x, state->dir_entries[i].name, state->dir_entries[i].is_dir, true);
        }
        else
        {
            render_item(main_window, y, x, state->dir_entries[i].name, state->dir_entries[i].is_dir, false);
        }
        ++y;
    }
    wrefresh(main_window);
}
