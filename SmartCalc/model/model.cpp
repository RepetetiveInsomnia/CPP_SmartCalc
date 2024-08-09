#include "model.h"

namespace s21 {

long double Model::calculate(const std::string &expression,
                             double x_placeholder) {
  auto queue = parser_.parseExpression(expression);

  long double result = 0;

  result = simple_math(queue, x_placeholder);

  return result;
}

long double Model::simple_math(std::queue<Token> &queue, double x_placeholder) {
  std::stack<long double> result_stack;
  Operations operation_;
  long double result = 0.0;
  long double number = 0.0;
  long double second_number = 0.0;
  while (!queue.empty()) {
    if (queue.front().isOperand() ||
        (queue.front().isOperator() &&
         queue.front().getOperator() == Operations::X)) {
      if (queue.front().getOperator() == Operations::X) {
        result_stack.push(x_placeholder);

      } else {
        result_stack.push(queue.front().getOperand());
      }
      queue.pop();
      if ((result_stack.empty() &&
           queue.front().getOperator() == Operations::X) ||
          queue.empty()) {
        throw MathException("Incorrect expression");
      }

    } else {
      operation_ = queue.front().getOperator();
      queue.pop();
      number = result_stack.top();
      result_stack.pop();
      if (operation_ >= Operations::U_PLUS) {
        result = calculator_.applyCalculations(operation_, number);
      } else if (result_stack.empty()) {
        throw MathException("Incorrect expression");
      } else {
        second_number = result_stack.top();
        result_stack.pop();
        result =
            calculator_.applyCalculations(operation_, second_number, number);
      }
      result_stack.push(result);
    }
  }
  result = result_stack.top();

  return result;
}

} // namespace s21
