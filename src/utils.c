/*  Utilities  */

#pragma once

#include "global.h"

void quit(WINDOW *main_window)
{
    delwin(main_window);
    endwin();
}

void exit_with_success(WINDOW *main_window)
{
    quit(main_window);
    exit(EXIT_SUCCESS);
}

void exit_with_failure(WINDOW *main_window)
{
    quit(main_window);
    exit(EXIT_FAILURE);
}

/*
 Using curses with `initscr()` or `newterm()` makes it impossible to also pipe output into some other Linux utility.
 Instead, we use `/dev/tty` for both input and output so the result of this program could be easily piped.
*/
void pipe_curses_output_to_stdout()
{
    FILE *tty = fopen("/dev/tty", "r+");
    SCREEN *screen = newterm(NULL, tty, tty);
    set_term(screen);
}

void detect_version_argument(WINDOW *main_window, char *user_input)
{
    if (strcmp(user_input, "-v") == 0)
    {
        render_version();
        exit_with_success(main_window);
    }
}

void get_size_window(WINDOW *main_window, struct app_state *state)
{
    getmaxyx(stdscr, state->window_rows, state->window_cols);
    state->window_rows = state->window_rows - WINDOW_SAFE_MARGIN_ROWS;
    state->window_cols = state->window_cols - WINDOW_SAFE_MARGIN_COLS;
}
