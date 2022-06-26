/*  Entry point and curses specifics */

#include "global.h"
#include "items.c"
#include "render.c"
#include "inputs.c"
#include "utils.c"

int main(int argc, char *argv[])
{
    pipe_curses_output_to_stdout();

    curs_set(0);

    struct app_state state = {};
    state.user_highlight = 0;
    state.window_rows_scroll = 0;

    clear();
    noecho();
    cbreak();

    WINDOW *main_window = render_window();

    scrollok(main_window, true);
    get_size_window(main_window, &state);

    validate_inputs(main_window, argc, argv);

    detect_version_argument(main_window, argv[1]);

    initializa_state(&state, argv[1]);
    render(main_window, &state);

    detect_key_pressed(main_window, &state);

    clrtoeol();
    quit(main_window);
    return 0;
}
