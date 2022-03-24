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

int main()
{
    struct appstate app_state = {};

    get_cwd(&app_state);

    printf("cwd is %s", app_state.cwd);

    return 0;
}