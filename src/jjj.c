#include "global.h"
#include "items.c"
#include "render.c"
#include "inputs.c"

int main()
{

    initscr();

    struct AppState state = {};
    state.user_highlight = 1;
    state.user_choice = 0;

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
