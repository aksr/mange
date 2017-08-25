#include "mange.h"

int commandLine(int argc, char **argv) {
	int i,in_file=0,plot_me=0;
	char line[MAXLINE];
	for (i = 1; i < argc; i++) {
		if (argv[i][0] != '-') {
			readFile(argv[i]);
			strcpy(buffer_name,argv[i]);
			in_file = 2;
		}
		else {
			switch (argv[i][1]) {
				case 'h':	// help
					// display help
					break;
				case 's':	// separator
					delim=argv[i][2];
					if (delim=='\0') {
						delim=',';
						fprintf(stderr,"Warning: Bad separator assignment.  Using default ','.\n");
					}
					break;
				case 'i':	// pipe input
					in_file=1;
					break;
				case 'p':	// plot and quit
					plot_me = i;
					break;
				default:
					fprintf(stderr,"Unknown command line argument: %s\nType %s -h for help.\n",argv[i],argv[0]);
					exit(1);
					break;
			}
		}
		if (plot_me > 0)
			break;
	}
	if (in_file == 1) {
		FILE *tmpFile=fopen("/tmp/mangeIn","w");
		while (scanf("%[^\n]\n",line) > 0)
			fprintf(tmpFile,"%s\n",line);
		fclose(tmpFile);
		freopen("/dev/tty","r",stdin);
		readFile("/tmp/mangeIn");
		strcpy(buffer_name,"FromStdIn.csv");
	}
	if (in_file == 0)
		readFile(" ");
	if (plot_me > 0) {
		if (in_file == 0) {
			fprintf(stderr,"No data available to plot\n");
			safeQuit();
		}
		if (argc < plot_me + 2) {
			fprintf(stderr,"No plot parameters provided\n");
			safeQuit();
		}
		writeFile("/tmp/mangeplot.csv");
#ifndef __NO_PLOT__
		plotBuffer(argc - plot_me,&argv[plot_me]);
#else
		fprintf(stderr,"Plotting module disabled\n");
#endif
		safeQuit();
	}
	return 0;
}
