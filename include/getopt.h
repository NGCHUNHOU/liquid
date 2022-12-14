#ifndef GETOPT_H__
#define GETOPT_H__

#ifdef __cplusplus
extern "C" {
#endif

extern char *optarg;
extern int optind;

#define no_argument 0
#define required_argument 1
#define optional_argument 2

struct option {
	const char* name;
	int has_arg;
	int *flag;
	int val;
};

struct argCounter { int fileCount = 0; int flagCount = 0; };

class argParser {
public:
	static int getArgType(int num);
	static int getopt_long(int argc, char* argv[], const char *short_opt, argCounter *aC);
};

#ifdef __cplusplus
}
#endif

#endif
