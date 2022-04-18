#include "header/global.h"

void detect_mouse(struct AppState *state)
{
    while (1)
    {
        state->key_pressed = wgetch(menu_win);
        switch (state->key_pressed)
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
            state->choice = state->highlight;
            break;
        default:
            refresh();
            break;
        }
        render_menu(menu_win, state);
        if (state->choice != 0) /* User did a choice come out of the infinite loop */
            break;
    }
    clrtoeol();
    refresh();
}
