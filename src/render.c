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

void render_dir_items(struct AppState *state)
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
    render_dir_items(state);
    refresh();
};

void render_window()
{
    menu_win = newwin(HEIGHT, WIDTH, RENDER_START_Y, RENDER_START_X);
    keypad(menu_win, TRUE);
    refresh();
}

void render_menu(WINDOW *menu_win, struct AppState *app_state)
{
    int x, y, i;

    x = 2;
    y = 2;

    for (i = 0; i <= app_state->dir_entries_total; ++i)
    {
        if (app_state->user_highlight == i + 1) /* High light the present choice */
        {
            wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, y, x, "%s", app_state->dir_entries[i].name);
            wattroff(menu_win, A_REVERSE);
        }
        else
        {
            mvwprintw(menu_win, y, x, "%s", app_state->dir_entries[i].name);
        }
        ++y;
    }
    wrefresh(menu_win);
}
