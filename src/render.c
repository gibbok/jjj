#pragma once
#include "header/global.h"

void render_window()
{
    menu_win = newwin(HEIGHT, WIDTH, RENDER_START_Y, RENDER_START_X);
    keypad(menu_win, TRUE);
    refresh();
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
    mvwprintw(menu_win, RENDER_START_Y + 22, x, "user_choice %d\n", state->user_choice);
    mvwprintw(menu_win, RENDER_START_Y + 23, x, "cwd %s\n", state->cwd);

    for (i = 0; i <= state->dir_entries_total; ++i)
    {
        if (state->user_highlight == i + 1) /* High light the present choice */
        {
            wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, y, x, "%s", state->dir_entries[i].name);
            wattroff(menu_win, A_REVERSE);
        }
        else
        {
            mvwprintw(menu_win, y, x, "%s", state->dir_entries[i].name);
        }
        ++y;
    }
    wrefresh(menu_win);
}
