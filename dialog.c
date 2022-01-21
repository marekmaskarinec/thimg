#include <stdio.h>
#include <stdlib.h>
#include "umka_api.h"

void c_getFile(UmkaStackSlot *par, UmkaStackSlot *r) {
	char *buf = (char *)par[0].ptrVal;
#ifdef __linux__
	FILE *p = popen(
		"zenity --file-selection --file-filter '*.png *.jpg *.bmp'", "r");
	if (!p) {
		printf("thimg: couldn't open pipe to zenity.");
		exit(1);
	}
	char c;
	for (int i=0; (c = fgetc(p)) != EOF && c != '\n'; i++)
		buf[i] = c;
	pclose(p);
#else
#error thimg can't open a file dialog on this platform
#endif
}
