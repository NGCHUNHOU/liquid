#include <iostream>
#include <array>
#include <getopt.h>
#include <imageHandler.h>
using namespace std;

void usage() {
	const char *programName = "liquid";
	const char* programDescription = "display or edit media files";
	const char* helpFlag = "-h, --help	display help and exit";
	const char* showallFlag = "-a, --all	show all info";
	printf("%s [OPTIONS] [FILES]\n%s\n\n %s\n %s", programName, programDescription, helpFlag, showallFlag);
	exit(0);
	return;
}

void try_openimg(int arg_c, char **arg_v, argCounter* argCt) {
	if (arg_c == 2 && argCt->flagCount == 0) {
		cout << "opening single file" << endl;
		imageHandler::openImg(arg_v[1]);
		exit(0);
	} else if (arg_c > 2 && argCt->fileCount == (arg_c - 1)) {
		cout << "all arguments type are file" << endl;
		imageHandler::openMultipleImgs(arg_v, arg_c);
		exit(0);
	} else if (arg_c > 2 && argCt->flagCount > 0) {
		cout << "the arguments have option flag and value" << endl;
		// opemMultipleImgWithFlag() here
	} else {
		return;
	}
}

int main(int argc, char** argv) {
	if (argc < 2) {
		cout << "no argument found" << endl;
		return 1;
	};

	char* flags = "h:a:";
	option opts[] = {
		{"help", optional_argument,  (int*)&flags[0], 1},
		{"all", optional_argument,  (int*)&flags[0], 2}
	};

	argCounter ac;
	char opt = NULL;
	while ((opt = argParser::getopt_long(argc, argv, flags, &ac)) != -1 && (ac.fileCount + ac.flagCount) < argc) {
		switch (opt) {
		case 'h':
			usage();
			break;
		case 'a':
			cout << "show all page" << endl;
			break;
		case '%':
			try_openimg(argc, argv, &ac);
			break;
		default:
			cout << "unknown option" << endl;
			break;
		};
	};
	return 0;
};
