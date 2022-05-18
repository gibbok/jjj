#include "global.h"
#include "items.c"
#include "render.c"
#include "inputs.c"

int main()
{

    FILE *tty = fopen("/dev/tty", "r+");
    SCREEN *screen = newterm(NULL, tty, tty);
    set_term(screen);

    struct AppState state = {};
    state.user_highlight = 1;

    update_state(&state);

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
