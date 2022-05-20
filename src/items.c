#pragma once
#include "global.h"
#include "render.c"

// Get current working directory
void get_cwd(struct AppState *state)
{
    char cwd[256]; // FIXME: find a way to make it platform indipendent
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("getcwd() error");
    }
    else
    {
        strcpy(state->cwd, cwd);
    }
}

// List directory in application state
void list_dir(struct AppState *state)
{
    state->dir_entries = malloc((2* sizeof(struct AppState)));

    struct dirent *dir_entry;

    DIR *dr = opendir(state->cwd);

    if (dr == NULL)
        printf("Could not open current directory");

    int i = 0;
    while ((dir_entry = readdir(dr)) != NULL)
    {
        state->dir_entries = realloc(state->dir_entries, sizeof(struct AppState) * 2 + i);
        struct DirItem item = {};
        strcpy(item.name, dir_entry->d_name);

        switch (dir_entry->d_type)
        {
        case DT_DIR:
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

    closedir(dr);
}

// Change directory
void change_directory(struct AppState *state)
{
    int idx = state->user_highlight;
    chdir(state->dir_entries[idx].name);
}

void reset_state(struct AppState *state)
{
    for (int i = 0; i <= state->dir_entries_total; ++i)
    {
        state->dir_entries[i].is_dir = 0;
        strcpy(state->dir_entries[i].name, "");
    }
    state->user_highlight = 0;
    state->dir_entries_total = 0;
}

// Change directory up
void change_directory_up(struct AppState *state)
{
    chdir("..");
}

void update_state(struct AppState *state)
{
    get_cwd(state);
    list_dir(state);
}

void refresh_screen(struct AppState *state)
{
    reset_state(state);
    update_state(state);
    render(menu_win, state);
    wclear(menu_win);
}
