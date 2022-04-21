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
