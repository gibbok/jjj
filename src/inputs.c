#pragma once
#include "global.h"

void bye(void)
{
    printf("That was all, folks\n");
}

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
        case KEY_L:
            change_directory(state);
            refresh_screen(state);
            break;
        case KEY_LEFT:
        case KEY_H:
            change_directory_up(state);
            refresh_screen(state);
            break;
        case KEY_Q:
        case KEY_ESC:
            endwin();
            printf("That was all, folks\n");
            exit(EXIT_SUCCESS);
            break;
        case KEY_ENTER:
        case KEY_SPACEBAR:
            exit(0);
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
