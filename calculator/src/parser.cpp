#include <cstdlib>
#include <unistd.h>
#include <climits>
#include <cerrno>
#include <cstring>
#include "parser.h"

void parse(int argc, char **argv, Data *data) {
  int opt;
  long value;
  char *endptr;

  while ((opt = getopt(argc, argv, "a:b:o:h")) != -1) {
    switch (opt) {
    case 'a':
      errno = 0;
      value = strtol(optarg, &endptr, 10);
      if (errno == ERANGE || *endptr != '\0' || value > INT_MAX || value < INT_MIN) {
        data->op = 'e';
      } else {
        data->num1 = (int)value;
      }
      break;
    case 'b':
      errno = 0;
      value = strtol(optarg, &endptr, 10);
      if (errno == ERANGE || *endptr != '\0' || value > INT_MAX || value < INT_MIN) {
        data->op = 'e';
      } else {
        data->num2 = (int)value;
      }
      break;
    case 'o':
      if (data->op == 'e') break; 
      if (optarg[0] == '*' || strlen(optarg) > 1) { data->op = '*'; }
      else { data->op = optarg[0]; }
      break;
    case 'h':
      data->op = 'h';
      break;
    }
  }
}
