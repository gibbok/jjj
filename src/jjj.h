#pragma once

struct AppState
{
    char cwd[256];
};

void update_cwd(struct AppState record);