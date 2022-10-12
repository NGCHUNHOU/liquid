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

	char opt = argParser::getopt_long(argc, argv, flags, opts);
	while (true) {
		if (argParser::getArgType(opt) == 2) {
			cout << "unknown option" << endl;
			break;
		};

		if (argParser::getArgType(opt) == 1) {
			cout << "reading file" << endl;
			break;
		}

		switch (opt) {
			case 'h':
				cout << "help page" << endl;
				break;

			case 'a':
				cout << "show all page" << endl;
				break;
		};

		if (argParser::getArgType(opt) == 3) 
			break;
	};

	return 0;
};
