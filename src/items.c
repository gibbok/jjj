/*  File system operations related to retrieving files and directories information. */

#pragma once

#include "global.h"
#include "render.c"

void reset_app_state(struct app_state *state)
{
    state->user_highlight = 0;
    state->dir_entries_total = 0;
    state->window_rows_scroll = 0;
}

void get_cwd(struct app_state *state)
{
    char cwd[FILENAME_MAX];
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

void list_items_in_dir(struct app_state *state)
{
    int allocation_count = 1;
    int allocation_size = 500;

    state->dir_entries = malloc((sizeof(struct app_state) * allocation_size));

    if (state->dir_entries == NULL)
    {
        printf("jjj: Error: Could not allocate memory.");
    }

    struct dirent *dir_entry;

    DIR *dr = opendir(state->cwd);

    if (dr == NULL)
    {
        printf("jjj: Error: Could not open directory %s.", state->cwd);
    }

    int i = 0;

    while ((dir_entry = readdir(dr)) != NULL)
    {
        if (i == allocation_size)
        {
            ++allocation_count;
            allocation_size = allocation_size * allocation_count;
            state->dir_entries = realloc(state->dir_entries, sizeof(struct app_state) * allocation_size);
        }

        if (state->dir_entries == NULL)
        {
            printf("jjj: Error: Could not resize memory.");
        }

        struct dir_item item = {};
        strcpy(item.name, dir_entry->d_name);

        switch (dir_entry->d_type)
        {
        case DT_DIR:
            /* Excludes special name-inode from the result of the list. */
            if (strcmp(dir_entry->d_name, ".") == 0 ||
                strcmp(dir_entry->d_name, "..") == 0)
            {
                break;
            }
            item.is_dir = true;
            state->dir_entries[i] = item;
            ++i;
            state->dir_entries_total = i;
            break;
        case DT_REG:
            item.is_dir = false;
            state->dir_entries[i] = item;
            ++i;
            state->dir_entries_total = i;
            break;
        default:
            break;
        }
    }

    closedir(dr);

    qsort(state->dir_entries, state->dir_entries_total, sizeof(struct dir_item), sorting_comparator);
}

void change_dir(struct app_state *state)
{
    int idx = state->user_highlight;
    chdir(state->dir_entries[idx].name);
}

void change_dir_up(struct app_state *state)
{
    if (strcmp(state->cwd, "/") > 0)
    {
        chdir("..");
    }
}

void set_cwd_to_user_path(struct app_state *state, char *user_path)
{
    char *user_full_path = realpath(user_path, NULL);
    strcpy(state->cwd, user_full_path);
}

void initializa_state(struct app_state *state, char *user_path)
{
    set_cwd_to_user_path(state, user_path);
    list_items_in_dir(state);
}

void update_app_state(struct app_state *state)
{
    reset_app_state(state);
    get_cwd(state);
    list_items_in_dir(state);
}
