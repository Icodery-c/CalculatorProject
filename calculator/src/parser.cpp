#include <stdlib.h>
#include <unistd.h>

#include "parser.h"

void parse(int argc, char **argv, Data *data) {

  int opt;

  while ((opt = getopt(argc, argv, "a:b:o:h")) != -1) {

    switch (opt) {

    case 'a':
      data->num1 = atoi(optarg);
      break;

    case 'b':
      data->num2 = atoi(optarg);
      break;

    case 'o':
      data->op = optarg[0];
      break;

    case 'h':
      data->op = 'h';
      break;
    }
  }
}
