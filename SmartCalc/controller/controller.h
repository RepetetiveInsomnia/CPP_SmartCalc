#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#pragma once

#include <cmath>
#include <cstdarg>
#include <map>
#include <string>

#include "../common/operations_list.h"
#include "../model/model.h"
#include "../model/model_graph.h"
namespace s21 {

class Controller {
public:
  const std::string line_update(const Operations &operation) noexcept;
  double expr_to_model(std::string expr);
  void expr_to_graph(const std::string expr, QVector<double> *x,
                     QVector<double> *y, double x_min_num, double x_max_num,
                     double y_min_num, double y_max_num, double points);
  bool check_x(std::string expr) noexcept;

private:
};

} // namespace s21

#endif // CONTROLLER_H_
