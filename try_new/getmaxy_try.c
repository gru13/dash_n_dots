#include <curses.h>

int main() {
  WINDOW *win;
  int maxx, maxy;

  win = initscr();
  getmaxyx(win, maxy, maxx);
  printw("The maximum x coordinate is %d.\n", maxx);
  printw("The maximum y coordinate is %d.\n", maxy);
  refresh();
  getch();
  endwin();

  return 0;
}