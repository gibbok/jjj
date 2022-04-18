#include "header/global.h"

void detect_mouse(struct AppState *state)
{
    while (1)
    {
        state->user_key_pressed = wgetch(menu_win);
        switch (state->user_key_pressed)
        {
        case KEY_UP:
            if (state->user_highlight == 1)
                state->user_highlight = state->dir_entries_total;
            else
                --state->user_highlight;
            break;
        case KEY_DOWN:
            if (state->user_highlight == state->dir_entries_total)
                state->user_highlight = 1;
            else
                ++state->user_highlight;
            break;
        case 10:
            state->user_choice = state->user_highlight;
            break;
        default:
            refresh();
            break;
        }
        render_menu(menu_win, state);
        if (state->user_choice != 0) /* User did a choice come out of the infinite loop */
            break;
    }
    clrtoeol();
    refresh();
}
