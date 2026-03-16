#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
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
      if (optarg[0] == '*' || strlen(optarg) > 1) { data->op = '*'; }
      else { data->op = optarg[0]; }
      break;

    case 'h':
      data->op = 'h';
      break;
    }
  }
}
