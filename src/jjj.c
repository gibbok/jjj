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

    get_cwd(&state);
    list_dir(&state);

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
