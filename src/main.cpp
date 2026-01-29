#include <iostream>
#include <array>
#include <getopt.h>
#include <imageHandler.h>
#include <memory>

void usage() {
	const char *programName = "liquid";
	const char* programDescription = "display or edit media files";
	const char* helpFlag = "-h, --help	display help and exit";
	const char* showallFlag = "-a, --all	show all info";
	printf("%s [OPTIONS] [FILES]\n%s\n\n %s\n %s", programName, programDescription, helpFlag, showallFlag);
	exit(0);
	return;
}

void try_openimg(char **arguments_vector_pointer, int arguments_count, int fileCount, int flagCount) {
  windowSize winSize = {static_cast<int>(sf::VideoMode::getDesktopMode().width * 0.8f), static_cast<int>(sf::VideoMode::getDesktopMode().height * 0.8f)};
	sf::RenderWindow window(sf::VideoMode(winSize.width, winSize.height), "Liquid");
  sf::View view;
	view.setSize(winSize.width, winSize.height);
	view.setCenter(view.getSize().x / 2, view.getSize().y / 2);

  imageHandler imgHandler;
  imgHandler.initWindowFrame(window, view, winSize);

	if (arguments_count == 2 && flagCount == 0) {
		std::cout << "opening single file\n";
		imgHandler.openSingleImage(arguments_vector_pointer[1]);
		exit(0);
	} else if (arguments_count > 2 && fileCount == (arguments_count - 1)) {
		std::cout << "all arguments type are file\n";
		imgHandler.openMultipleImages(arguments_vector_pointer, arguments_count);
		exit(0);
	} else if (arguments_count > 2 && flagCount > 0) {
		std::cout << "the arguments have option flag and value\n";
	} else {
		return;
	}
}

int main(int argc, char** argv) {
	if (argc < 2) {
		std::cout << "no argument found\n";
		return 1;
	};

	char flags[64] = "h:a:";
	option opts[] = {
		{"help", optional_argument,  (int*)&flags[0], 1},
		{"all", optional_argument,  (int*)&flags[0], 2}
	};

	argCounter arg_counter = {0, 0, argc, argv};
	argParser arg_parser(argc, argv);
	char opt = '\0';
	while ((opt = arg_parser.getopt_long(flags)) != '\0') {
		switch (opt) {
		case 'h':
			usage();
			break;
		case 'a':
			std::cout << "show all page\n";
			break;
		case '%':
			try_openimg(arg_parser.get_arguments_vector_pointer(), arg_parser.arguments_count, arg_parser.fileCount, arg_parser.flagCount);
			break;
		default:
			std::cout << "unknown option\n";
			break;
		};
	};
	return 0;
};
