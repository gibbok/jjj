#pragma once
struct appstate
{
    char cwd[256];
};

void get_cwd(struct appstate *state);
