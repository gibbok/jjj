
/*  Detect user interactions with the program.  */

#pragma once

#include "global.h"

void select_prev_item(struct app_state *state)
{
    if (state->user_highlight == 0)
        state->user_highlight = state->dir_entries_total - 1;
    else
        --state->user_highlight;
}

void select_next_item(struct app_state *state)
{
    if (state->user_highlight == state->dir_entries_total - 1)
        state->user_highlight = 0;
    else
        ++state->user_highlight;
}

void visit_selected_item(struct app_state *state)
{
    change_directory(state);
    refresh_screen(state, true);
}

void visit_parent_item(struct app_state *state)
{
    change_directory_up(state);
    refresh_screen(state, true);
}

void return_selected_item(struct app_state *state)
{
    endwin();
    render_active_item(state);
    free(state->dir_entries);
    exit(EXIT_SUCCESS);
}

void detect_key_pressed(struct app_state *state)
{
    while (1)
    {
        state->user_key_pressed = wgetch(menu_win);
        switch (state->user_key_pressed)
        {
        case KEY_UP:
        case KEY_K:
            select_prev_item(state);
            break;
        case KEY_DOWN:
        case KEY_J:
            select_next_item(state);
            break;
        case KEY_RIGHT:
        case KEY_L:
            visit_selected_item(state);
            break;
        case KEY_LEFT:
        case KEY_H:
            visit_parent_item(state);
            break;
        case KEY_Q:
        case KEY_ESC:
        case KEY_SPACEBAR:
        case KEY_RETURN:
            return_selected_item(state);
            break;
        case KEY_R:
            refresh_screen(state, true);
            break;
        default:
            refresh();
            break;
        }
        render(menu_win, state);
    }
    clrtoeol();
    refresh();
}
