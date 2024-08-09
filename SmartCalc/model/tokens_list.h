#ifndef TOKENS_LIST_H_
#define TOKENS_LIST_H_

#pragma once

#include "../common/operations_list.h"

namespace s21 {

struct Token { // Use a struct only for passive objects that carry data;
               // everything else is a class - согласно google style
  union Value {
    long double operand_;
    Operations operator_;
  };

  enum Type { OPERAND, OPERATOR };

  Type type_;
  Value value_;

  static Token Operand(long double operand) {
    return Token{OPERAND, {operand}};
  }

  static Token Operator(Operations m_operator) {
    return Token{OPERATOR, {.operator_ = m_operator}};
  }

  bool isOperand() { return type_ == OPERAND; }

  bool isOperator() { return type_ == OPERATOR; }

  long double getOperand() const { return value_.operand_; }

  Operations getOperator() const { return value_.operator_; }
};

} // namespace s21

#endif // TOKENS_LIST_H_
