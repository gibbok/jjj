/*  Entry point and curses specifics */

#include "global.h"
#include "items.c"
#include "render.c"
#include "inputs.c"

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

void detect_version_argument(char *user_input)
{
    if (strcmp(user_input, "-v") == 0)
    {
        render_version();
        exit_with_success();
    }
}

void get_size_window(WINDOW *main_window, struct app_state *state)
{
    getmaxyx(stdscr, state->window_row, state->window_col);
    state->window_row = state->window_row - WINDOW_SAFE_MARGIN_Y;
    state->window_col = state->window_col - WINDOW_SAFE_MARGIN_X;
}

int main(int argc, char *argv[])
{
    pipe_curses_output_to_stdout();

    curs_set(0);

    struct app_state state = {};
    state.user_highlight = 0;
    state.window_row_scroll = 0;

    clear();
    noecho();
    cbreak();

    WINDOW *main_window = render_window();

    scrollok(main_window, true);
    get_size_window(main_window, &state);

    validate_inputs(argc, argv);

    detect_version_argument(argv[1]);

    initializa_state(&state, argv[1]);
    render(main_window, &state);

    detect_key_pressed(main_window, &state);

    clrtoeol();
    endwin();
    return 0;
}
