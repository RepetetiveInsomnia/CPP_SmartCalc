#include "calculator.h"

#include <iostream>
namespace s21 {

const std::map<Operations, Calculator::BinaryOperation>
    Calculator::binary_operations = {{Operations::ADD, &Calculator::add},
                                     {Operations::SUB, &Calculator::sub},
                                     {Operations::MUL, &Calculator::mul},
                                     {Operations::DIV, &Calculator::div},
                                     {Operations::POW, &Calculator::pow},
                                     {Operations::MOD, &Calculator::mod}};

const std::map<Operations, Calculator::UnaryOperation>
    Calculator::unary_operations = {
        {Operations::U_PLUS, &Calculator::uPlus},
        {Operations::U_MINUS, &Calculator::uMinus},
        {Operations::COS, &Calculator::cos},
        {Operations::SIN, &Calculator::sin},
        {Operations::TAN, &Calculator::tan},
        {Operations::ACOS, &Calculator::acos},
        {Operations::ASIN, &Calculator::asin},
        {Operations::ATAN, &Calculator::atan},
        {Operations::SQRT, &Calculator::sqrt},
        {Operations::LN, &Calculator::ln},
        {Operations::LOG, &Calculator::log},
};

long double Calculator::applyCalculations(Operations operation, ...) {
  va_list args;
  va_start(args, operation);

  long double result = 0.0;

  if (unary_operations.count(operation)) {
    long double num = va_arg(args, long double);
    result = (*this.*unary_operations.at(operation))(num);
  } else {
    long double num1 = va_arg(args, long double);
    long double num2 = va_arg(args, long double);
    result = (*this.*binary_operations.at(operation))(num1, num2);
  }

  va_end(args);
  return result;
}

long double Calculator::add(long double num1, long double num2) noexcept {
  return num1 + num2;
}

long double Calculator::sub(long double num1, long double num2) noexcept {
  return num1 - num2;
}

long double Calculator::mul(long double num1, long double num2) noexcept {
  return num1 * num2;
}

long double Calculator::div(long double num1, long double num2) {
  if (num2 == 0.0)
    throw MathException("Division by zero");

  return num1 / num2;
}

long double Calculator::pow(long double num1, long double num2) noexcept {
  return powl(num1, num2);
}

long double Calculator::mod(long double num1, long double num2) noexcept {
  return fmod(num1, num2);
}

long double Calculator::uPlus(long double num) noexcept { return +num; }

long double Calculator::uMinus(long double num) noexcept { return -num; }

long double Calculator::cos(long double num) noexcept { return cosl(num); }

long double Calculator::sin(long double num) noexcept { return sinl(num); }

long double Calculator::tan(long double num) noexcept { return tanl(num); }

long double Calculator::acos(long double num) noexcept { return acosl(num); }

long double Calculator::asin(long double num) noexcept { return asinl(num); }

long double Calculator::atan(long double num) noexcept { return atanl(num); }

long double Calculator::sqrt(long double num) noexcept { return sqrtl(num); }

long double Calculator::ln(long double num) noexcept { return logl(num); }

long double Calculator::log(long double num) noexcept { return log10l(num); }

} // namespace s21
