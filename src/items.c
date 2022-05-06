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

// List directory in application state
void list_dir(struct AppState *state)
{
    struct dirent *dir_entry;

    DIR *dr = opendir(state->cwd);

    if (dr == NULL)
        printf("Could not open current directory");

    int i = 0;
    while ((dir_entry = readdir(dr)) != NULL)
    {
        struct DirItem item = {};
        strcpy(item.name, dir_entry->d_name);
        if (dir_entry->d_type == DT_DIR)
            item.is_dir = 1;
        else
            item.is_dir = 0;

        state->dir_entries[i] = item;
        ++i;
        state->dir_entries_total = i;
    }

    closedir(dr);
}

// Change directory
void change_directory(struct AppState *state)
{
    int idx = state->user_highlight - 1;
    chdir(state->dir_entries[idx].name);
    get_cwd(state);
    list_dir(state);
}
