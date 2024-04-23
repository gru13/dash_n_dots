#include<stdio.h>
#include<c


int main() {
    // Initialize curses
    initscr(); // Initialize the screen

    // Check if terminal supports colors
    if (has_colors()) {
        start_color(); // Enable color
        init_pair(1, COLOR_RED, COLOR_BLACK); // Define color pair
    }

    // Print a message in the center of the screen
    mvprintw(LINES / 2, (COLS - 20) / 2, "Hello PDCurses!");

    // Display a colored message
    if (has_colors()) {
        attron(COLOR_PAIR(1)); // Activate color pair
        mvprintw(LINES / 2 + 1, (COLS - 24) / 2, "This is a red message!");
        attroff(COLOR_PAIR(1)); // Deactivate color pair
    }

    // Refresh the screen to display changes
    refresh();

    // Wait for user input
    getch(); // Wait for user input

    // Clean up and exit
    endwin(); // End curses mode

    return 0;
}
