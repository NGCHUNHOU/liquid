#include <getopt.h>
#include <windows.h>

char* optarg = NULL;
int optind = 1;

int argParser::getArgType(int num) {
	// 001 filearg, 010 unknown flag, 011 onlyFlag
	int bits = 0;
	if (num == -1) {
		bits |= 1;
		return bits;
	};
	if (num == '?') {
		bits |= 1 << 1;
		return bits;
	} else {
		return num;
	};
};

int argParser::getopt_long(int argc, char* const argv[], const char* short_opt, argCounter *aC)
{
	if ((optind >= argc) || (argv[optind][0] == 0))
		return -1;

	int firstChar = 0;

	if (argv[optind][0] != '-') {
		aC->fileCount += 1;
		return '%';
	} else if (argv[optind][1] == '-') {
		firstChar = argv[optind][2];
		aC->flagCount += 1;
	}
	else {
		firstChar = argv[optind][1];
		aC->flagCount += 1;
	}

	if (aC->fileCount > 0)
		return firstChar + ((aC->fileCount)+(aC->flagCount));

	const char* p = strchr(short_opt, firstChar);

	if (p == NULL) {
		optind++;
		return '?';
	};

	if (p[1] == ':')
	{
		optarg = argv[optind];
		optind++;
	};

	if (((aC->fileCount) + (aC->flagCount)) <= 2) {
		return firstChar;
	};
	return firstChar + ((aC->fileCount)+(aC->flagCount));
};
