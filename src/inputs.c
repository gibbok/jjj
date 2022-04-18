#include "header/global.h"

void detect_mouse(struct AppState *state)
{
    while (1)
    {
        USER_KEY_PRESSED = wgetch(menu_win);
        switch (USER_KEY_PRESSED)
        {
        case KEY_UP:
            if (state->highlight == 1)
                state->highlight = state->dir_entries_total;
            else
                --state->highlight;
            break;
        case KEY_DOWN:
            if (state->highlight == state->dir_entries_total)
                state->highlight = 1;
            else
                ++state->highlight;
            break;
        case 10:
            choice = state->highlight;
            break;
        default:
            refresh();
            break;
        }
        render_menu(menu_win, state);
        if (choice != 0) /* User did a choice come out of the infinite loop */
            break;
    }
    clrtoeol();
    refresh();
}
