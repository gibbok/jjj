#pragma once
#include "global.h"

// Print to screen results
void render_cwd(struct AppState *state)
{
    printf("%s\n", state->cwd);
}

void render_dir_items_total(struct AppState *state)
{
    printf("Total: %i\n", state->dir_entries_total);
}

void render_dir_items(struct AppState *state)
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
