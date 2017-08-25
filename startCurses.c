#include "mange.h"

int startCurses() {
    initscr();
    if(has_colors() == FALSE) {
        endwin();
        printf("Your terminal does not support color\n");
        exit(1);
    }
    start_color();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    nonl();
    curs_set(0);
    getmaxyx(stdscr,MaxRows,MaxCols);
	MaxRows --;
    use_default_colors();
    init_pair(1,COLOR_WHITE,-1);
    init_pair(2,COLOR_GREEN,-1);
    init_pair(3,COLOR_YELLOW,-1);
    init_pair(4,COLOR_RED,-1);
    init_pair(5,COLOR_MAGENTA,-1);
    init_pair(6,COLOR_CYAN,-1);
    init_pair(7,COLOR_BLUE,COLOR_BLACK);
	init_pair(8,COLOR_BLACK,COLOR_GREEN);
	init_pair(9,COLOR_BLACK,COLOR_WHITE);
	init_pair(10,COLOR_BLACK,COLOR_CYAN);
	init_pair(11,COLOR_BLACK,COLOR_YELLOW);
	init_pair(12,COLOR_WHITE,COLOR_BLACK);
	return 0;
}

