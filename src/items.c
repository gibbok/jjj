/*  File system operations related to retrieving files and directories information. */

#pragma once

#include "global.h"
#include "render.c"

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
    
    free(state->dir_entries);
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

    qsort(state->dir_entries, state->dir_entries_total, sizeof(struct dir_item), sorting_comparator);

    closedir(dr);
}

void change_dir(struct app_state *state)
{
    int idx = state->user_highlight;
    chdir(state->dir_entries[idx].name);
}

void reset_app_state(struct app_state *state)
{
    for (int i = 0; i <= state->dir_entries_total; ++i)
    {
        state->dir_entries[i].is_dir = false;
        strcpy(state->dir_entries[i].name, "");
    }
    state->user_highlight = 0;
    state->dir_entries_total = 0;
}

void change_dir_up(struct app_state *state)
{
    chdir("..");
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
    get_cwd(state);
    list_items_in_dir(state);
}

bool is_active_item_dir(struct app_state *state)
{
    return state->dir_entries[state->user_highlight].is_dir;
}

void refresh_screen(WINDOW *main_window, struct app_state *state)
{
    bool can_reset = is_active_item_dir(state);
    if (can_reset == true)
    {
        reset_app_state(state);
    }
    update_app_state(state);
    render(main_window, state);
    wclear(main_window);
}
