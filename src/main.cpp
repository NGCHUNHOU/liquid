#include <iostream>
#include <array>
#include <getopt.h>
#include <fstream>
#include <imageHandler.h>
using namespace std;

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
			cout << "help page" << endl;
			break;
		case 'a':
			cout << "show all page" << endl;
			break;
		default:
			break;
		};
	};
	
	if (ac.fileCount == argc) {
		cout << "all arguments type are file" << endl;

		ifstream file(argv[1]);
		if (!file.good()) {
			cout << "failed to open the images" << endl;
			return 1;
		};

		imageHandler::openImg(argv[1]);
		return 0;
	};

	if (argc == 2) {
		cout << "show nothing because option is printed" << endl;
		return 0;
	};

	cout << "option and file" << endl;

	return 0;

};
