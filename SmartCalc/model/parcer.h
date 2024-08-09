#ifndef PARCER_H_
#define PARCER_H_

#pragma once

#include <map>
#include <queue>
#include <stack>
#include <string>

#include "../common/calc_exception.h"
#include "../common/operations_list.h"
#include "tokens_list.h"

namespace s21 {

class Parser {
public:
  std::queue<Token> parseExpression(const std::string &expression);

private:
  std::stack<Token> tokens_stack_{};
  std::queue<Token> tokens_queue_{};

  void pullStackToQueue();
  Operations operations_map(const std::string &expression, const char **shift);
  void
  removeFirstCharsFromExpression(std::string &expression,
                                 std::string::difference_type count) noexcept;

  void parseX(std::string &expression) noexcept;
  void parseNumber(std::string &expression) noexcept;
  void parseOpenBracket(std::string &expression) noexcept;
  void parseCloseBracket(std::string &expression);
  void parseFunction(std::string &expression) noexcept;
  void parseOperation(std::string &expression) noexcept;
  void parceunaryOperator(std::string &expression);

  void pushNumberToQueue(const long double &number) noexcept;
  void pushXToQueue(const Operations &operation) noexcept; // возможно убрать
  void pushOperatorToQueue(const Operations &operation) noexcept;
  void pushOperatorToStack(const Operations &operation) noexcept;

  bool hasLowerPriority(Operations operation) noexcept;
  bool isUnaryOperator(Operations operation, std::string &expression) noexcept;

  bool isOperator(const std::string &expression);
  bool isFunction(const std::string &expression);
  bool isCloseBracket(char ch) noexcept;
  bool isOpenBracket(char ch) noexcept;
  bool isDot(char ch) noexcept;
  bool isDigit(char ch) noexcept;
  bool isX(char ch) noexcept;
};

} // namespace s21

#endif // PARCER_H_
