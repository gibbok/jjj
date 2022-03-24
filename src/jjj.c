#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

struct AppState
{
    char cwd[256];
};

char MAX_BUF;

int main()
{
    struct AppState app_state = {};

    printf("Hello, World!\n");

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