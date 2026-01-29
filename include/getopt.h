#ifndef GETOPT_H__
#define GETOPT_H__
#include <string>

#define no_argument 0
#define required_argument 1
#define optional_argument 2

struct option {
	const char* name;
	int has_arg;
	int *flag;
	int val;
};

struct argCounter { int fileCount; int flagCount; int arguments_count; char **arguments_vector; };

class argParser {
private:
  std::string option_value = "";
  int option_index = 1;
  char **arguments_vector_pointer = nullptr;
public:
  int fileCount = 0;
  int flagCount = 0;
  const int arguments_count;
	static int getArgType(int num);
	int getopt_long(const char *short_opt);
  argParser(const int arguments_count_input, char **arguments_vector_pointer_input) : arguments_count(arguments_count_input), arguments_vector_pointer(arguments_vector_pointer_input) {};

  char** get_arguments_vector_pointer();
};

#endif
