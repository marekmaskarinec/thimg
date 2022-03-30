#include <stdio.h>
#include <stdlib.h>
#include "umka_api.h"

#ifdef _WIN32
#include <windows.h>
#include <commdlg.h>

int openDialog(char *buf) {
	OPENFILENAME ofn;

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = buf;
	ofn.lpstrFile[0] = '\0';
	ofn.lpstrFilter = "All\0*.*\0Images\0*.bmp;*.png;*.jpg\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir=NULL;
	ofn.nMaxFile = 4096;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	return GetOpenFileName(&ofn);
}
#endif

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
#elif _WIN32
	openDialog(par[0].ptrVal);
#else
	fprintf(stderr, "Thimg can't open a file dialog on this platform.")
#error thimg can't open a file dialog on this platform
#endif
}
