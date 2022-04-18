#include "header/global.h"

void detect_mouse(struct AppState *state)
{
    while (1)
    {
        c = wgetch(menu_win);
        switch (c)
        {
        case KEY_UP:
            if (highlight == 1)
                highlight = state->dir_entries_total;
            else
                --highlight;
            break;
        case KEY_DOWN:
            if (highlight == state->dir_entries_total)
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
        render_menu(menu_win, highlight, state);
        if (choice != 0) /* User did a choice come out of the infinite loop */
            break;
    }
    clrtoeol();
    refresh();
}
