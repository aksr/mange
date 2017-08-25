#include "mange.h"

int insertCell(int ii,int ij) {
	char *tptr;
	int ti,tj;
    int c = msgLine(COLOR_MODES,MSG_KEY,"[INS] ^Column, ^Row?");
//	int c = msgLine(COLOR_MODES,MSG_KEY,"[INS] ^Column, ^Row, ^Entry?");
    switch (c) {
        case 'r':
        	saved=0;
			buffer = realloc(buffer,((rows+1)*cols+1) * sizeof(char *));
			for (ti = 0; ti < cols; ti++)
				getField(ti,rows) = (char *) malloc(col_width[ti]);
			for (ti = 0; ti < cols; ti++) {
				tptr = getField(ti,rows);
				for (tj = rows; tj > ij; tj--)
					getField(ti,tj) = getField(ti,tj-1);
				getField(ti,ij)=tptr;
			}
			for (ti = 0; ti < cols; ti++)
				setField(ti,ij,".");
			rows++;
            break;
        case 'c':
        	saved=0;
			buffer = realloc(buffer,(rows*(cols+2)+1) * sizeof(char *));
			col_width = (int *) realloc(col_width,(cols+1) * sizeof(int));
			for (ti = cols; ti > ii+1; ti--)
				col_width[ti]=col_width[ti-1];
			col_width[ii+1]=5;
			for (tj = rows; tj > 0; tj--) {
				for (ti = cols-1; ti > ii; ti--)
					getField(ti+tj,tj-1)=getField(ti,tj-1);
				getField(ii+tj,tj-1) = (char *) malloc(3);
				setField(ii+tj,tj-1,".");
				for (ti = ii-1; ti > -2; ti--)
					getField(ti+tj,tj-1)=getField(ti+1,tj-1);
			}
			cols++;
            break;
/*		case 'e':
        	saved=0;
			c = msgLine(COLOR_MODES,MSG_KEY,"[INS] Shift ^Right, Shift ^Down?");
            switch(c) {
				case 'R':
				case 'r':
				case KEY_RIGHT:
					tptr=getField(cols-1,ij);
					for (ti = cols-1; ti > ii; ti--)
						getField(ti,ij) = getField(ti-1,ij);
					getField(ii,ij) = tptr;
					setField(ii,ij,"");
					int tlen;
					for (ti = 0; ti < rows; ti ++) {
							tlen = strlen(getField(ti,ij));
							if (col_width[ti] < tlen)
								col_width[ti] = tlen;
					}
					break;
				case 'D':
				case 'd':
				case KEY_DOWN:
					tptr=getField(ii,rows-1);
					for (tj = rows-1; tj > ij; tj--)
						getField(ii,tj) = getField(ii,tj-1);
					getField(ii,ij) = tptr;
					setField(ii,ij,"");
					break;
				default:
					break;
			}
			break;	*/
		default:
			break;
	}
	return 0;
}
