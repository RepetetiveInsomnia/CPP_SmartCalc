#ifndef MODEL_GRAPH_H
#define MODEL_GRAPH_H
#pragma once
#include <QVector>

#include "model.h"
namespace s21 {
class Model_graph {
public:
  void calculate_graph(const std::string expr, QVector<double> *x,
                       QVector<double> *y, double x_min_num, double x_max_num,
                       double y_min_num, double y_max_num, double points);

private:
  Model model_;
};
} // namespace s21
#endif // MODEL_GRAPH_H
