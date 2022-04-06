#include "header/global.h"
#include "items.c"
#include "render.c"
#include "inputs.c"

int main()
{
    initscr();
    clear();
    noecho();
    cbreak();

    render_window();
    render_menu(menu_win, highlight);
    detect_mouse();

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