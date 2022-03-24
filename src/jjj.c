#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "jjj.h"

// https://fresh2refresh.com/c-programming/c-passing-struct-to-function/

void update_cwd(struct AppState record)
{
    printf(" Id is: %s \n", record.cwd);
}

// struct update_state_cwd(struct AppState app_state);

int main()
{
    struct AppState app_state = {};

    char cwd[256];

    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("getcwd() error");
    }
    else
    {
        strcpy(app_state.cwd, cwd);
        printf("current working directory is: %s\n", app_state.cwd);
    }

    return 0;
}