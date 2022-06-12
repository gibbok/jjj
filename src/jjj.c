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

int main()
{
    pipe_curses_output_to_stdout();

    curs_set(0);

    struct app_state state = {};
    state.user_highlight = 0;

    update_app_state(&state);

    clear();
    noecho();
    cbreak();

    render_window();
    render(menu_win, &state);

    detect_key_pressed(&state);

    clrtoeol();
    endwin();
    return 0;
}