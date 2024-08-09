#ifndef CALC_EXEPTION_H_
#define CALC_EXEPTION_H_

#pragma once

#include <stdexcept>

namespace s21 {

class MathException : public std::exception {
 public:
  MathException(const char *message) : message(message) {}
  ~MathException() noexcept override = default;

  const char *what() const noexcept override { return message; }

 private:
  const char *message;
};

}  // namespace s21

#endif  // CALC_EXEPTION_H_
