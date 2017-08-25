#include "mange.h"

char **buffer;
char buffer_name[MAXLINE];
char saved;
char delim = ',';
int undo_level;
int MaxRows,MaxCols;	// Screen resolution
int cols,rows;			// buffer cells
char curses_running;

int main(int argc, char ** argv) {
	int i=0,j=1,c,ret;
	commandLine(argc,argv);
	startCurses();
	curses_running=1;
	showBuffer(&i,&j);
	// main key loop:
	for (;;) {
		c = getch();
		switch (c) {
			case KEY_ENTER:
				setUndo();
				// if editCell returns next, go to next ...
				ret = editCell(i,j);
				while (ret != 0) {
					showBuffer(&i,&j);
					switch (ret) {
						case '\t':
							if (++i >= cols) {j++;i=0;}
							if (j >= rows) {i=0;j=1;}
							showBuffer(&i,&j);
							break;
						case KEY_ENTER:
							if (++j >= rows) {i++;j=1;}
							if (i >= cols) {i=0;j=1;}
							showBuffer(&i,&j);
							break;
						default:
							break;
					}
					ret = editCell(i,j);
				}
				break;
			case KEY_RIGHT:
				i++;
				break;
			case KEY_LEFT:
				i--;
				break;
			case KEY_DOWN:
				j++;
				break;
			case KEY_UP:
				j--;
				break;
			case KEY_NPAGE:
			case 'n':
				j += MaxRows - 4;
				break;
			case KEY_PPAGE:
			case 'p':
				j -= MaxRows - 4;
				break;
			case ':':
				commandMode();
				break;
			case 'd':
			case KEY_BACKSPACE:
			case KEY_DC:
			case KEY_CTL_K:
				setUndo();
				deleteCell(i,j);
				break;
			case KEY_IC:
			case 'i':
				setUndo();
				insertCell(i,j);
				break;
			case KEY_CTL_U:
				undoLast();
				break;
			case KEY_CTL_O:
				if (buffer_name != NULL)
					writeFile(buffer_name);
				break;
			case KEY_CTL_X:
				safeQuit();
				break;
			default:
				break;
		}
		showBuffer(&i,&j);
	}
	// Should never get here, if we do, return with error;
	freeBuffer();
	endwin();
	// temp files not deleted to allow for partial recovery of data if we somehow exit here.
	return 1;
}

int freeBuffer() {
    int i;
    for (i = 0; i < (cols * rows); i++)
        free(buffer[i]);
    free(buffer);
    free(col_width);
	return 0;
}

int safeQuit() {
    int ret = 0;
    if (saved == 0)
        ret = savePrompt();
    if (ret == 0) {
        freeBuffer();
        endwin();
        system("cd /tmp; rm mange* &> /dev/null");
        exit(0);
    }
	return 0;
}
