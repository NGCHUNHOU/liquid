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

int getopt_long(int argc, char* const argv[], const char *short_opt, option *long_opt);

#ifdef __cplusplus
}
#endif

#endif
