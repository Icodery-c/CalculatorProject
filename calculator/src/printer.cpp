#include <iostream>

#include "printer.h"

void print(Data *data, int error) {

  if (error) {
    std::cout << "Error" << std::endl;
    return;
  }

  std::cout << "Result = " << data->result << std::endl;
}

void help() {

  std::cout << "Инструкция по использованию калькулятора: " << std::endl;

  std::cout << "calculator -a NUM1 -b NUM2 -o OP" << std::endl;

  std::cout << "Возможные операции:" << std::endl;

  std::cout << "Cложение (+)" << std::endl;
  std::cout << "Вычитание (-)" << std::endl;
  std::cout << "Умножение (*)" << std::endl;
  std::cout << "Деление (/)" << std::endl;
  std::cout << "Возведение в степень (^)" << std::endl;
  std::cout << "Факториал (!)" << std::endl;
}
