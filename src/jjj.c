#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include "jjj.h"

void get_cwd(struct appstate *state)
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

void print_screen(struct appstate *state)
{
    printf("%s", state->cwd);
}

void list_dir(struct appstate *state)
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

        printf("--------------");
        printf("%s\n", dir_entry->d_name);
        printf("%i\n", i);
        i++;

        // printf("%s\n", dir_entry->d_type);
    }

    closedir(dr);
}

int main()
{
    struct appstate app_state = {};

    get_cwd(&app_state);

    print_screen(&app_state);

    list_dir(&app_state);

    return 0;
}