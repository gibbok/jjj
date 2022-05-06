#pragma once
#include "header/global.h"

void detect_mouse(struct AppState *state)
{
    while (1)
    {
        state->user_key_pressed = wgetch(menu_win);
        switch (state->user_key_pressed)
        {
        case KEY_UP:
        case KEY_K:
            if (state->user_highlight == 1)
                state->user_highlight = state->dir_entries_total;
            else
                --state->user_highlight;
            break;
        case KEY_DOWN:
        case KEY_J:
            if (state->user_highlight == state->dir_entries_total)
                state->user_highlight = 1;
            else
                ++state->user_highlight;
            break;
        case 10:
            state->user_choice = state->user_highlight;
            break;
        case KEY_RIGHT:
            change_directory(state);
            refresh_screen(state);
            break;
        case KEY_LEFT:
            change_directory_up(state);
            refresh_screen(state);
            break;
        default:
            refresh();
            break;
        }
        render(menu_win, state);
        if (state->user_choice != 0) /* User did a choice come out of the infinite loop */
            break;
    }
    clrtoeol();
    refresh();
}
