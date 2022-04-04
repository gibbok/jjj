#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include "header/global.h"
#include "items.c"
#include "render.c"

// List directory in application state
void list_dir(struct AppState *state)
{
    struct dirent *dir_entry;

    DIR *dr = opendir(state->cwd);

    if (dr == NULL)
        printf("Could not open current directory");

    int i = 0;
    while ((dir_entry = readdir(dr)) != NULL)
    {
        struct DirItem item = {};
        strcpy(item.name, dir_entry->d_name);
        if (dir_entry->d_type == DT_DIR)
            item.is_dir = 1;
        else
            item.is_dir = 0;

        state->dir_entries[i] = item;
        ++i;
        state->dir_entries_total = i;
    }

    closedir(dr);
}

int main()
{
    struct AppState app_state = {};

    get_cwd(&app_state);

    list_dir(&app_state);

    print_screen(&app_state);

    return 0;
}