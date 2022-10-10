#include <getopt.h>
#include <windows.h>

char* optarg = NULL;
int optind = 1;

int getopt_long(int argc, char* const argv[], const char* short_opt, option* long_opt)
{
	if ((optind >= argc) || (argv[optind][0] == 0) || (argv[optind][0] != '-') && (argv[optind][1] != '-') )
		return -1;

	int firstChar;

	if (argv[optind][1] != '-')
		firstChar = argv[optind][1];
	else
		firstChar = argv[optind][2];

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

	return firstChar;
};
