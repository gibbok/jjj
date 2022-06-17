/*  Detect user interactions with the program.  */

#pragma once

#include "global.h"

void exit_with_success()
{
    endwin();
    exit(EXIT_SUCCESS);
}

void exit_with_failure()
{
    endwin();
    exit(EXIT_FAILURE);
}

void validate_inputs(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("jjj: Error: Invalid input. A valid path is required.");
        exit_with_failure();
    }
    if (argc > 2)
    {
        printf("jjj: Error: Invalid input. Only a single relative or absolute valid path is required.");
        exit_with_failure();
    }
}

void select_prev_item(WINDOW *main_window, struct app_state *state)
{
    // if (state->user_highlight > 0)
    // {
    //     --state->user_highlight;
    // }
    if (state->user_highlight == 0)
        state->user_highlight = state->dir_entries_total - 1;
    else
        --state->user_highlight;
}

void select_next_item(WINDOW *main_window, struct app_state *state)
{
    // if (state->user_highlight < state->dir_entries_total - 1)
    // {
    //     ++state->user_highlight;
    // }
    if (state->user_highlight == state->dir_entries_total - 1)
        state->user_highlight = 0;
    else
        ++state->user_highlight;

    // SPO continue here
    if (state->user_highlight >= state->window_row)
    {
        wscrl(main_window, 1);
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

void return_selected_item(struct app_state *state)
{
    render_active_item(state);
    free(state->dir_entries);
    exit_with_success();
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
            return_selected_item(state);
            break;
        case KEY_Q:
        case KEY_ESC:
            exit_with_success();
        case KEY_R:
            update_app_state(state);
            break;
        }
        // clearok(main_window, true);
        render(main_window, state);
    }
}
