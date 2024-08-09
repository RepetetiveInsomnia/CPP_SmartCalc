#ifndef MODEL_H_
#define MODEL_H_

#pragma once

#include <iostream>

#include "calculator.h"
#include "parcer.h"

namespace s21 {

class Model {
public:
  long double calculate(const std::string &expression, double x_placeholder);

private:
  Calculator calculator_;
  Parser parser_;
  long double simple_math(std::queue<Token> &queue, double x_placeholder);
};

} // namespace s21

#endif // MODEL_H_
