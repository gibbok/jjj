#include "header/global.h"
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
    render_screen(&state);

    clear();
    noecho();
    cbreak();

    render_window();
    render_menu(menu_win, &state);
    detect_mouse(&state);

    clrtoeol();
    endwin();
    return 0;
}

// MY CODE
// int main()
// {
//     initscr();

//     struct AppState app_state = {};

//     get_cwd(&app_state);
//     list_dir(&app_state);
//     render_screen(&app_state);

//     getch();
//     endwin();

//     return 0;
// }