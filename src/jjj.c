#include "global.h"
#include "items.c"
#include "render.c"
#include "inputs.c"

int main()
{

    FILE *tty = fopen("/dev/tty", "r+");
    SCREEN *screen = newterm(NULL, tty, tty);
    curs_set(0);
    set_term(screen);

    struct app_state state = {};
    state.user_highlight = 0;

    update_state(&state);
    refresh_screen_periodically();

    clear();
    noecho();
    cbreak();

    render_window();
    render(menu_win, &state);

    detect_mouse(&state);

    clrtoeol();
    endwin();
    return 0;
}