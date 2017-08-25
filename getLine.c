#include "mange.h"

int getLine(char *line, int xpos, int ypos) {
	move(ypos,xpos);
	printw(line);
	curs_set(1);
	refresh();
	int i=strlen(line), c, t;
	c = getch();
	while ( (c != KEY_ENTER) && (c != '\t') ) {
		switch (c) {
			case KEY_BACKSPACE:
				if (i>0) {
					i--;
					for (t = i; t < strlen(line); t++)
						line[t] = line[t+1];
					move(ypos,xpos);
					printw("%s ",line);
					move(ypos,i +xpos);
					refresh();
				}
				break;
			case KEY_UP:
				if (history ==1) {
					strcpy(line,last_command);
					move(ypos,xpos);
					printw(line);
					refresh();
					i = strlen(line);
				}
			case KEY_DOWN:
				// what should down do?
				break;
			case KEY_LEFT:
				if (i>0) {
					move(ypos,--i+xpos);
					refresh();
				}
				break;
			case KEY_RIGHT:
				if (i<strlen(line)) {
					move(ypos,++i+xpos);
					refresh();
				}
				break;
			case KEY_DC:
				t = i;
				while (t < strlen(line))
					line[t] = line[++t];
				move(ypos,xpos);
				printw("%s ",line);
				move(ypos,i+xpos);
				refresh();
				break;
			default:
				t = strlen(line);
				line[t+1] = '\0';
				if (i < strlen(line))
					while (t > i)
						line[t] = line[--t];
				line[i] = c;
				move(ypos,xpos);
				printw(line);
				move(ypos,++i+xpos);
				refresh();
				break;
		}
		c = getch();
	}
    curs_set(0);
	refresh();
	return c;	// return the last key pressed
}

