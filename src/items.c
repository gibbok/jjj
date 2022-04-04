#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include "header/global.h"

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
