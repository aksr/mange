#ifndef __mange_h__
#define __mange_h__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

// Some additions to ncurses keys - these may need to changed on different systems
#define KEY_BACKSPACE	127
#define KEY_ENTER		13
#define KEY_CTL_X		24
#define KEY_CTL_K		11
#define KEY_CTL_U		21
#define KEY_CTL_O		15

#define MAXLINE			200
#define MAXFIELD		100

// definitions for msgLine()
#define MSG_GO		1
#define MSG_KEY		2
#define MSG_LINE	3
#define MSG_START	4

// internal color definitions
#define COLOR_NORMAL	COLOR_PAIR(1)
#define COLOR_HEADER	COLOR_PAIR(6)
#define COLOR_NORMALT	COLOR_PAIR(9)
#define COLOR_HEADALT	COLOR_PAIR(10)
#define COLOR_INFO		COLOR_PAIR(3)
#define COLOR_COMMAND	COLOR_PAIR(8)
#define COLOR_QUESTION	COLOR_PAIR(11)
#define COLOR_MODES		COLOR_PAIR(7)
#define COLOR_EDIT		COLOR_PAIR(11)
#define COLOR_ERROR		COLOR_PAIR(4)

// PLOTTING
#define SHOW_PLOT   "feh -F --zoom max /tmp/mangeplot.jpg &> /dev/null"

//  MACROS:
#define getField(x,y)		buffer[(y) * cols + x]
#define setField(x,y,v)		strcpy(buffer[(y) * cols + x],v)

// GLOBALS:
extern char **buffer;
extern char buffer_name[MAXLINE];
extern char saved;
extern char delim;
extern int undo_level;
extern int MaxRows,MaxCols;
extern int cols,rows;
extern int *col_width;
extern char curses_running;
extern char last_command[MAXLINE];
extern int history;

// FUNCTIONS:
int writeFile(char *);
int readFile(char *);
int commandLine(int, char **);
int setColWidth();
int showBuffer(int *, int *);
int startCurses();
int commandMode();
int deleteCell(int,int);
int insertCell(int,int);
int editCell(int, int);
int getLine(char *,int,int);
int msgLine(int,int,const char *);
int getX(int);
int getY(int);
int getColWidth(int);
int savePrompt();
int showText(FILE *);
int undoLast();
int setUndo();
int purgeUndos();
int safeQuit();
int freeBuffer();
#ifndef __NO_PLOT__
int plotBuffer(int, char **);
#endif	// __NO_PLOT__

#endif // __mange_h__
