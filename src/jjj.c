#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
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

int main()
{
    struct appstate app_state = {};

    get_cwd(&app_state);

    print_screen(&app_state);

    return 0;
}