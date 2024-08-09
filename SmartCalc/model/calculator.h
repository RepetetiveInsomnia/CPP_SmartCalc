#ifndef CALCULATOR_H_
#define CALCULATOR_H_

#pragma once

#include <cmath>
#include <cstdarg>
#include <map>

#include "../common/calc_exception.h"
#include "../common/operations_list.h"

namespace s21 {

class Calculator {
public:
  long double applyCalculations(Operations operation, ...);

  // Binary operations
  long double add(long double num1, long double num2) noexcept;
  long double sub(long double num1, long double num2) noexcept;
  long double mul(long double num1, long double num2) noexcept;
  long double div(long double num1, long double num2);
  long double pow(long double num1, long double num2) noexcept;
  long double mod(long double num1, long double num2) noexcept;

  // Unary operations
  long double uPlus(long double num) noexcept;
  long double uMinus(long double num) noexcept;
  long double cos(long double num) noexcept;
  long double sin(long double num) noexcept;
  long double tan(long double num) noexcept;
  long double acos(long double num) noexcept;
  long double asin(long double num) noexcept;
  long double atan(long double num) noexcept;
  long double sqrt(long double num) noexcept;
  long double ln(long double num) noexcept;
  long double log(long double num) noexcept;

private:
  using BinaryOperation = long double (Calculator::*)(long double, long double);
  using UnaryOperation = long double (Calculator::*)(long double);

  const static std::map<Operations, BinaryOperation> binary_operations;
  const static std::map<Operations, UnaryOperation> unary_operations;
};

} // namespace s21

#endif // CALCULATOR_H_
