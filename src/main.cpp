#include <iostream>
#include <array>
#include <SFML/Window.hpp>
#include <getopt.h>

using namespace std;

int main(int argc, char** argv) {
	if (argc < 2) {
		cout << "no argument found" << endl;
		return 1;
	};

	char *flags = "h:a:";
	option opts[] = { 
		{"help", optional_argument,  (int*)&flags[0], 1},
		{"all", optional_argument,  (int*)&flags[0], 2} 
	};

	bool is_filearg = 0;
	bool onlyFlag = 1;

	while (true) {
		char opt = getopt_long(argc, argv, flags, opts);

		// if no dashed arg found, set is_filearg to true
		if (opt == -1) {
			is_filearg = 1;
			break;
		};
		// if unknown option or unknown option without file arg, echo unknown option
		if (opt == '?') {
			cout << "unknown option" << endl;
			break;
		} else {
			onlyFlag = 0;
		};

		switch (opt) {
			case 'h':
				cout << "help page" << endl;
				break;

			case 'a':
				cout << "show all page" << endl;
				break;
		};
	};

	if (is_filearg && onlyFlag)
		cout << "reading file" << endl;

	return 0;
};
