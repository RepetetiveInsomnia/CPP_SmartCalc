#include "model_graph.h"

void s21::Model_graph::calculate_graph(const std::string expr,
                                       QVector<double> *x, QVector<double> *y,
                                       double x_min_num, double x_max_num,
                                       double y_min_mum, double y_max_mum,
                                       double points) {
  double step = (x_max_num - x_min_num) / points;
  double pre_y = 0.0;
  double X = x_min_num;
  for (X = x_min_num; X < x_max_num; X += step) {
    pre_y = model_.calculate(expr, X);
    x->push_back(X);
    if (pre_y < y_min_mum || pre_y > y_max_mum) {
      y->push_back(std::numeric_limits<double>::quiet_NaN());
    } else {
      y->push_back(pre_y);
    }
  }
}
