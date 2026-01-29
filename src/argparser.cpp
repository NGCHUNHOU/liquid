#include <getopt.h>
#include <iostream>
#include <windows.h>

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

int argParser::getopt_long(const char *short_opt) {
  // base case to stop looping the option values
	if (option_index > (arguments_count - 1)) {
		return '\0';
  }

  const int cli_parameters_count = arguments_count - 1;
	char firstChar = '\0';

	if (arguments_vector_pointer[option_index][0] != '-') {
		fileCount += 1;
		return '%';
	} else if (arguments_vector_pointer[option_index][1] == '-') {
		firstChar = arguments_vector_pointer[flagCount][2];
		flagCount += 1;
	} else {
		firstChar = arguments_vector_pointer[option_index][1];
		flagCount += 1;
	}

  option_index += 1;

	const char* character_found = std::strchr(short_opt, firstChar);
  if (character_found != nullptr) {
    return *character_found;
  }

  // unknown case
	return '?';
};

char** argParser::get_arguments_vector_pointer() { return arguments_vector_pointer; };
