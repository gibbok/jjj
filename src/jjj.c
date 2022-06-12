#include "global.h"
#include "items.c"
#include "render.c"
#include "inputs.c"

void use_ncourse_with_stout_stin()
{
    FILE *tty = fopen("/dev/tty", "r+");
    SCREEN *screen = newterm(NULL, tty, tty);
    set_term(screen);
}

int main()
{
    use_ncourse_with_stout_stin();
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