#include "parcer.h"

#include <iostream>
namespace s21 {

std::queue<Token> Parser::parseExpression(const std::string &expression) {
  tokens_stack_ = {};
  tokens_queue_ = {};
  std::string expr = expression;

  if (expr.empty())
    throw MathException("Empty expression");

  while (!expr.empty()) {
    if (expr.front() == ' ') {
      removeFirstCharsFromExpression(
          expr, 1); // потенциально решение пробелов додумать
    } else if (isX(expr.front())) {
      parseX(expr);
    } else if (isDigit(expr.front()))
      parseNumber(expr);
    else if (isOpenBracket(expr.front())) {
      parseOpenBracket(expr);
      if (isOperator(expr)) {
        parceunaryOperator(expr); // trouble
      }
    } else if (isFunction(expr))
      parseFunction(expr);
    else if (isOperator(expr)) {
      parseOperation(expr);
      if (isOperator(expr)) {
        parceunaryOperator(expr);
      }

    } else if (isCloseBracket(expr.front()))
      parseCloseBracket(expr);
    else if (isDot(expr.front()))
      throw MathException("Extra decimal dot");
    else
      throw MathException("Unsupported operation");
  }

  pullStackToQueue();

  return tokens_queue_;
}

// utility func
Operations Parser::operations_map(const std::string &expression,
                                  const char **shift) {
  static std::map<std::string, Operations> operations_keys = {
      // вынести отдельнло
      {"x", Operations::X},       {"+", Operations::ADD},
      {"-", Operations::SUB},     {"*", Operations::MUL},
      {"/", Operations::DIV},     {"^", Operations::POW},
      {"mod", Operations::MOD},   {"+", Operations::U_PLUS},
      {"-", Operations::U_MINUS}, {"cos", Operations::COS},
      {"sin", Operations::SIN},   {"tan", Operations::TAN},
      {"acos", Operations::ACOS}, {"asin", Operations::ASIN},
      {"atan", Operations::ATAN}, {"sqrt", Operations::SQRT},
      {"ln", Operations::LN},     {"log", Operations::LOG}};
  for (const auto &op : operations_keys) {
    if (expression.compare(0, op.first.length(), op.first) == 0) {
      *shift = expression.c_str() + op.first.length();
      return op.second;
    }
  }

  throw MathException("Unsupported operation"); // добавить позже, пока что
}
void Parser::removeFirstCharsFromExpression(
    std::string &expression, std::string::difference_type count) noexcept {
  expression.erase(expression.begin(), expression.begin() + count);
}
bool Parser::hasLowerPriority(Operations operation) noexcept {
  int result = false;
  if (!tokens_stack_.empty()) {
    Operations operation_in_stack = tokens_stack_.top().getOperator();
    bool operations_with_equal_priority =
        (operation == Operations::SUB && operation_in_stack == Operations::ADD);
    bool lower_priority = (operation_in_stack < Operations::OP_BRACKET &&
                           operation_in_stack >= operation);
    result = (operations_with_equal_priority || lower_priority);
  }
  return result;
}
void Parser::pullStackToQueue() {
  while (!tokens_stack_.empty()) {
    if (tokens_stack_.top().getOperator() == Operations::OP_BRACKET ||
        tokens_stack_.top().getOperator() == Operations::CL_BRACKET)
      throw MathException("No closing bracket");
    else {
      pushOperatorToQueue(tokens_stack_.top().getOperator());
      tokens_stack_.pop();
    }
  }
}
// pushing funk
void Parser::pushXToQueue(const Operations &operation) noexcept {
  tokens_queue_.push(Token::Operator(operation));
}
void Parser::pushNumberToQueue(const long double &number) noexcept {
  tokens_queue_.push(Token::Operand(number));
}
void Parser::pushOperatorToQueue(const Operations &operation) noexcept {
  tokens_queue_.push(Token::Operator(operation));
}

void Parser::pushOperatorToStack(const Operations &operation) noexcept {
  tokens_stack_.push(Token::Operator(operation));
}
// parsing func
void Parser::parseX(std::string &expression) noexcept {
  const char *shift;
  Operations func = operations_map(expression, &shift);
  pushXToQueue(func);
  removeFirstCharsFromExpression(expression, shift - expression.c_str());
}
void Parser::parseNumber(std::string &expression) noexcept {
  char *shift;
  long double number = strtold(expression.c_str(), &shift);
  pushNumberToQueue(number);
  removeFirstCharsFromExpression(expression, shift - expression.c_str());
}

void Parser::parseFunction(std::string &expression) noexcept {
  const char *shift;
  Operations func = operations_map(expression, &shift);
  pushOperatorToStack(func);
  removeFirstCharsFromExpression(expression, shift - expression.c_str());
}

void Parser::parseOperation(std::string &expression) noexcept {
  const char *shift;
  Operations operation = operations_map(expression, &shift);
  if (isUnaryOperator(operation, expression))
    operation = (operation == Operations::ADD) ? Operations::U_PLUS
                                               : Operations::U_MINUS;
  while (hasLowerPriority(operation)) {
    pushOperatorToQueue(tokens_stack_.top().getOperator());
    tokens_stack_.pop();
  }

  pushOperatorToStack(operation);
  removeFirstCharsFromExpression(expression, shift - expression.c_str());
}

void Parser::parseOpenBracket(std::string &expression) noexcept {
  pushOperatorToStack(Operations::OP_BRACKET);
  removeFirstCharsFromExpression(expression, 1);
}

void Parser::parseCloseBracket(std::string &expression) {
  while (!tokens_stack_.empty() &&
         tokens_stack_.top().getOperator() != Operations::OP_BRACKET) {
    pushOperatorToQueue(tokens_stack_.top().getOperator());
    tokens_stack_.pop();
  }
  if (!tokens_stack_.empty() &&
      tokens_stack_.top().getOperator() == Operations::OP_BRACKET)
    tokens_stack_.pop();
  else
    throw MathException("No opening bracket");
  if (!tokens_stack_.empty() &&
      (tokens_stack_.top().getOperator() < Operations::OP_BRACKET &&
       tokens_stack_.top().getOperator() >= Operations::COS)) {
    pushOperatorToQueue(tokens_stack_.top().getOperator());
    tokens_stack_.pop();
  }
  removeFirstCharsFromExpression(expression, 1);
  if (!expression.empty() && !isOperator(expression) &&
      !isCloseBracket(expression.front())) {
    throw MathException("Incorrect expression_nothig after bracket");
  }
}
// searching func
bool Parser::isUnaryOperator(Operations operation,
                             std::string &expression) noexcept {
  bool plus_or_minus =
      (operation == Operations::ADD || operation == Operations::SUB);
  bool conditions_for_unary =
      (tokens_queue_.empty() || isOpenBracket(*(expression.c_str() - 1)) ||
       isOperator(expression.c_str() - 1));

  return plus_or_minus && conditions_for_unary;
}
bool Parser::isOperator(const std::string &expression) {
  try {
    const char *shift;
    Operations operation = operations_map(expression, &shift);
    return (operation >= Operations::ADD && operation < Operations::COS);
  } catch (const MathException &e) {
    return false;
  }
}
void Parser::parceunaryOperator(std::string &expression) {
  const char *shift;
  Operations unary_operation = operations_map(expression, &shift);
  if (unary_operation == Operations::ADD) {
    unary_operation = Operations::U_PLUS;
    while (hasLowerPriority(unary_operation)) {
      pushOperatorToQueue(tokens_stack_.top().getOperator());
      tokens_stack_.pop();
    }
    pushOperatorToStack(unary_operation);
    removeFirstCharsFromExpression(expression, shift - expression.c_str());
  } else if (unary_operation == Operations::SUB) {
    unary_operation = Operations::U_MINUS;
    while (hasLowerPriority(unary_operation)) {
      pushOperatorToQueue(tokens_stack_.top().getOperator());
      tokens_stack_.pop();
    }
    pushOperatorToStack(unary_operation);
    removeFirstCharsFromExpression(expression, shift - expression.c_str());
  } else {
    throw MathException("Incorrect expression_at parce unary op");
  }
}
bool Parser::isFunction(const std::string &expression) {
  try {
    const char *shift;
    Operations function = operations_map(expression, &shift);
    return (function >= Operations::COS && function < Operations::OP_BRACKET);
  } catch (const MathException &e) {
    return false;
  }
}
bool Parser::isCloseBracket(char ch) noexcept { return ch == ')'; }
bool Parser::isOpenBracket(char ch) noexcept { return ch == '('; }
bool Parser::isDot(char ch) noexcept { return ch == '.'; }
bool Parser::isX(char ch) noexcept { return ch == 'x'; }
bool Parser::isDigit(char ch) noexcept { return isdigit(ch); }
} // namespace s21
