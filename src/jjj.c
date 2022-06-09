#include "global.h"
#include "items.c"
#include "render.c"
#include "inputs.c"

int RUNNING = 1;

void *foo(void *vargp) {
  while(RUNNING) {
    printf("bar\n");
    sleep(1); // one second
  }
  return NULL;
}

int main()
{
    pthread_t thread_foo;
    pthread_create(&thread_foo, NULL, foo, NULL);
    sleep(4);
    RUNNING = 0;
    pthread_join(thread_foo, NULL);

    FILE *tty = fopen("/dev/tty", "r+");
    SCREEN *screen = newterm(NULL, tty, tty);
    curs_set(0);
    set_term(screen);

    struct app_state state = {};
    state.user_highlight = 0;

    update_state(&state);

    clear();
    noecho();
    cbreak();

    render_window();
    render(menu_win, &state);

    detect_mouse(&state);

    clrtoeol();
    endwin();
    return 0;
}