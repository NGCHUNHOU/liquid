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

void try_openimg(argCounter& argCt) {
	sf::RenderWindow window(sf::VideoMode(imageHandler::winSize.width, imageHandler::winSize.height), "Liquid");
  imageHandler imgHandler;
  imgHandler.initArgCounter(argCt);
  imgHandler.initWindow(window);

	if (argCt.arguments_count == 2 && argCt.flagCount == 0) {
		cout << "opening single file" << endl;
		imageHandler::openImage(argCt.arguments_vector[1]);
		exit(0);
	} else if (argCt.arguments_count > 2 && argCt.fileCount == (argCt.arguments_count - 1)) {
		cout << "all arguments type are file" << endl;
		imgHandler.openMultipleImages();
		exit(0);
	} else if (argCt.arguments_count > 2 && argCt.flagCount > 0) {
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

	argCounter arg_counter = {0, 0, argc, argv};
	char opt = NULL;
	while ((opt = argParser::getopt_long(arg_counter.arguments_count, arg_counter.arguments_vector, flags, &arg_counter)) != -1 && (arg_counter.fileCount + arg_counter.flagCount) < arg_counter.arguments_count) {
		switch (opt) {
		case 'h':
			usage();
			break;
		case 'a':
			cout << "show all page" << endl;
			break;
		case '%':
			try_openimg(arg_counter);
			break;
		default:
			cout << "unknown option" << endl;
			break;
		};
	};
	return 0;
};
