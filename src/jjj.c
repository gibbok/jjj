#include "header/global.h"
#include "items.c"
#include "render.c"

int main()
{
    struct AppState app_state = {};

    get_cwd(&app_state);

    list_dir(&app_state);

    render_screen(&app_state);

    return 0;
}