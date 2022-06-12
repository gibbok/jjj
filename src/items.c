/*  File system operations related to retrieving files and directories information. */

#pragma once

#include "global.h"
#include "render.c"

void get_cwd(struct app_state *state)
{
    char cwd[256];
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("getcwd() error");
    }
    else
    {
        strcpy(state->cwd, cwd);
    }
}

int sorting_comparator(const void *d1, const void *d2)
{
    return (strcmp(((struct dir_item *)d1)->name, ((struct dir_item *)d2)->name));
}

void list_dir(struct app_state *state)
{
    state->dir_entries = malloc((2 * sizeof(struct app_state)));

    struct dirent *dir_entry;

    DIR *dr = opendir(state->cwd);

    if (dr == NULL)
        printf("Could not open directory %s", state->cwd);

    int i = 0;
    while ((dir_entry = readdir(dr)) != NULL)
    {
        state->dir_entries = realloc(state->dir_entries, sizeof(struct app_state) * 2 + i);
        struct dir_item item = {};
        strcpy(item.name, dir_entry->d_name);

        switch (dir_entry->d_type)
        {
        case DT_DIR:
            /* Excludes special name-inode from the result of the list. */
            if (strcmp(dir_entry->d_name, ".") == 0)
                break;
            if (strcmp(dir_entry->d_name, "..") == 0)
                break;
            item.is_dir = 1;
            state->dir_entries[i] = item;
            ++i;
            state->dir_entries_total = i;
            break;
        case DT_REG:
            item.is_dir = 0;
            state->dir_entries[i] = item;
            ++i;
            state->dir_entries_total = i;
            break;
        default:
            break;
        }
    }

    qsort(state->dir_entries, state->dir_entries_total, sizeof(struct dir_item), sorting_comparator);

    closedir(dr);
}

void change_directory(struct app_state *state)
{
    int idx = state->user_highlight;
    chdir(state->dir_entries[idx].name);
}

void reset_state(struct app_state *state)
{
    for (int i = 0; i <= state->dir_entries_total; ++i)
    {
        state->dir_entries[i].is_dir = 0;
        strcpy(state->dir_entries[i].name, "");
    }
    state->user_highlight = 0;
    state->dir_entries_total = 0;
}

void change_directory_up(struct app_state *state)
{
    chdir("..");
}

void update_state(struct app_state *state)
{
    get_cwd(state);
    list_dir(state);
}

void refresh_screen(struct app_state *state, bool can_reset)
{
    if (can_reset)
        reset_state(state);
    update_state(state);
    render(menu_win, state);
    wclear(menu_win);
}
