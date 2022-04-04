#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include "header/global.h"

// Print to screen results
void render_cwd(struct AppState *state)
{
    printf("%s\n", state->cwd);
}

void render_dir_items_total(struct AppState *state)
{
    printf("Total: %i\n", state->dir_entries_total);
}

void print_dir_items(struct AppState *state)
{
    int i;
    for (i = 0; i < state->dir_entries_total; ++i)
    {
        struct DirItem item = state->dir_entries[i];
        if (item.is_dir == 1)
            printf("%s/\n", item.name);
        else
            printf("%s\n", item.name);
    }
}

void render_screen(struct AppState *state)
{
    system("clear");
    render_cwd(state);
    render_dir_items_total(state);
    print_dir_items(state);
};