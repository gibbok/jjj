/*  Detect user interactions with the program.  */

#pragma once

#include "global.h"
#include "utils.c"

void validate_inputs(WINDOW *main_window, int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("jjj: Error: Invalid input. A valid path is required.");
        exit_with_failure(main_window);
    }
    if (argc > 2)
    {
        printf("jjj: Error: Invalid input. Only a single relative or absolute valid path is required.");
        exit_with_failure(main_window);
    }
}

void select_prev_item(WINDOW *main_window, struct app_state *state)
{
    if (state->user_highlight > 0)
    {
        --state->user_highlight;
    }

    if (state->user_highlight >= state->window_rows)
    {
        --state->window_rows_scroll;
    }
    else
    {
        state->window_rows_scroll = 0;
    }
}

void select_next_item(WINDOW *main_window, struct app_state *state)
{
    if (state->user_highlight < state->dir_entries_total - 1)
    {
        ++state->user_highlight;
    }

    if (state->user_highlight >= state->window_rows)
    {
        if (state->window_rows_scroll + state->window_rows < state->dir_entries_total)
        {
            ++state->window_rows_scroll;
        }
    }
    else
    {
        state->window_rows_scroll = 0;
    }
}

void visit_selected_item(WINDOW *main_window, struct app_state *state)
{
    change_dir(state);
    update_app_state(state);
}

void visit_parent_item(WINDOW *main_window, struct app_state *state)
{
    change_dir_up(state);
    update_app_state(state);
}

void return_selected_item(WINDOW *main_window, struct app_state *state)
{
    render_active_item(state);
    free(state->dir_entries);
    exit_with_success(main_window);
}

void detect_key_pressed(WINDOW *main_window, struct app_state *state)
{
    while (1)
    {
        state->user_key_pressed = wgetch(main_window);
        switch (state->user_key_pressed)
        {
        case KEY_UP:
        case KEY_K:
            select_prev_item(main_window, state);
            break;
        case KEY_DOWN:
        case KEY_J:
            select_next_item(main_window, state);
            break;
        case KEY_RIGHT:
        case KEY_L:
            visit_selected_item(main_window, state);
            break;
        case KEY_LEFT:
        case KEY_H:
            visit_parent_item(main_window, state);
            break;
        case KEY_SPACEBAR:
        case KEY_RETURN:
            return_selected_item(main_window, state);
            break;
        case KEY_Q:
        case KEY_ESC:
            exit_with_success(main_window);
        case KEY_R:
            update_app_state(state);
            break;
        }

        update_screen(main_window, state);
    }
}
