#include "runner.h"
#include "calculator.h"
#include "checker.h"
#include "parser.h"
#include "printer.h"

void run(int argc, char **argv) {

  Data data{0};

  int error = 0;

  parse(argc, argv, &data);

  if (data.op == 'h') {
    help();
    return;
  }

  error = check(&data);

  if (!error) {
    error = calculate(&data);
  }

  print(&data, error);
}
