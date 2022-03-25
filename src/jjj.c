#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include "jjj.h"

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

// Print to screen results
void print_cwd(struct AppState *state)
{
    printf("%s\n", state->cwd);
}

void print_dir_items_total(struct AppState *state)
{
    printf("Total: %i\n", state->dir_entries_total);
}

void print_dir_items(struct AppState *state)
{
    int i;
    for (i = 0; i < state->dir_entries_total; ++i)
    {
        printf("%d - %s - %d\n", i, state->dir_entries[i].name, state->dir_entries[i].is_dir);
    }
}

void print_screen(struct AppState *state)
{
    print_cwd(state);
    print_dir_items_total(state);
    print_dir_items(state);
};

// List directory in application state
void list_dir(struct AppState *state)
{
    struct dirent *dir_entry;

    DIR *dr = opendir(state->cwd);

    if (dr == NULL)
    {
        printf("Could not open current directory");
    }

    int i = 0;
    while ((dir_entry = readdir(dr)) != NULL)
    {
        struct DirItem item = {};
        strcpy(item.name, dir_entry->d_name);
        if (dir_entry->d_type == DT_DIR)
        {

            item.is_dir = 1;
        }
        else
        {
            item.is_dir = 0;
        }

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