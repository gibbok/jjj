/*  Render the application state into the terminal. */

#pragma once

#include "global.h"

WINDOW *render_window()
{
    WINDOW *main_window = newwin(0, 0, RENDER_AT_WINDOW_POSITION_ROWS, RENDER_AT_WINDOW_POSITION_COLS);
    keypad(main_window, TRUE);
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

    x = RENDER_AT_WINDOW_POSITION_COLS;
    y = RENDER_AT_WINDOW_POSITION_ROWS + 1;

    mvwprintw(main_window, RENDER_AT_WINDOW_POSITION_ROWS, x, "%s", state->cwd);

    if (DEBUG_MODE == 1)
    {
        int x_debug = state->window_col - 30;
        mvwprintw(main_window, RENDER_AT_WINDOW_POSITION_ROWS + 1, x_debug, "user_highlight %d\n", state->user_highlight);
        mvwprintw(main_window, RENDER_AT_WINDOW_POSITION_ROWS + 2, x_debug, "user_key_pressed %d\n", state->user_key_pressed);
        mvwprintw(main_window, RENDER_AT_WINDOW_POSITION_ROWS + 3, x_debug, "dir_entries_total %d\n", state->dir_entries_total);
        mvwprintw(main_window, RENDER_AT_WINDOW_POSITION_ROWS + 4, x_debug, "window_row %d\n", state->window_row);
        mvwprintw(main_window, RENDER_AT_WINDOW_POSITION_ROWS + 5, x_debug, "window_col %d\n", state->window_col);
        mvwprintw(main_window, RENDER_AT_WINDOW_POSITION_ROWS + 6, x_debug, "window_row_scroll %d\n", state->window_row_scroll);
    }

    for (i = 0 + state->window_row_scroll; i <= state->dir_entries_total; ++i)
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
}

void render_version()
{
    printf("jjj version: %s", APP_VERSION);
}
