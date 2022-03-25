#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include "jjj.h"

// Get current working directory
void get_cwd(struct AppState *state)
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

// Print to screen results
void print_screen(struct AppState *state)
{
    printf("%s", state->cwd);
}

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
        // create item to push in my data structure
        struct DirItem item = {};
        strcpy(item.name, dir_entry->d_name);
        item.is_dir = 1;

        state->dir_entries[i] = item;

        printf("--------------");
        printf("%s\n", state->dir_entries[i].name);
        printf("%i\n", i);
        i++;

        // printf("%s\n", dir_entry->d_type);
    }

    closedir(dr);
}

int main()
{
    struct AppState app_state = {};

    get_cwd(&app_state);

    print_screen(&app_state);

    list_dir(&app_state);

    return 0;
}