#include "./dash_n_dots.h"


int main() {
    initscr(); // Initialize curses
    curs_set(0);
    WINDOW* win = newwin(HYT, WDT, 0, 0); // Create a new window
    if (win == NULL) {
        endwin(); // Clean up curses
        fprintf(stderr, "Error: Unable to create window.\n\n");
        return 1;
    }

    initBoard(win);

    // mvwprintw(win, 0, 0, "g"); // Print message in the window
    // mvwprintw(win, 0, 1, "g"); // Print message in the window
    // wrefresh(win); // Refresh the window

    Sleep(2000); // Sleep for 2 seconds

    delwin(win); // Delete the window
    endwin(); // End curses

    return 0;
}
// gcc main.c  -o main.exe  -lncurses;.\main.exe