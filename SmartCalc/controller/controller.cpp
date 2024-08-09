#include "controller.h"

#include <sstream>
namespace s21 {

const std::string
Controller::line_update(const Operations &operation) noexcept {
  static std::map<Operations, std::string> operations_keys = {
      {Operations::X, "x"},          {Operations::ADD, "+"},
      {Operations::SUB, "-"},        {Operations::MUL, "*"},
      {Operations::DIV, "/"},        {Operations::POW, "^"},
      {Operations::MOD, "mod"},      {Operations::U_PLUS, "+"},
      {Operations::U_MINUS, "-"},    {Operations::COS, "cos("},
      {Operations::SIN, "sin("},     {Operations::TAN, "tan("},
      {Operations::ACOS, "acos("},   {Operations::ASIN, "asin("},
      {Operations::ATAN, "atan("},   {Operations::SQRT, "sqrt("},
      {Operations::LN, "ln("},       {Operations::LOG, "log("},
      {Operations::OP_BRACKET, "("}, {Operations::CL_BRACKET, ")"}};
  std::string result;
  for (const auto &op : operations_keys)
    if (operation == op.first) {
      result = op.second;
    }
  return result;
}
bool Controller::check_x(const std::string expr) noexcept {
  bool result = false;
  if (expr.find('x') == std::string::npos) {
    result = true;
  }
  return result;
}
void Controller::expr_to_graph(const std::string expr, QVector<double> *x,
                               QVector<double> *y, double x_min_num,
                               double x_max_num, double y_min_mum,
                               double y_max_mum, double points) {
  Model_graph model_;
  model_.calculate_graph(expr, x, y, x_min_num, x_max_num, y_min_mum, y_max_mum,
                         points);
}
double Controller::expr_to_model(const std::string expr) {
  double result = 0;
  Model model_;
  result = model_.calculate(expr, 0);
  return result;
}
} // namespace s21
