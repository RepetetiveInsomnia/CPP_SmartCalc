#include "dialog.h"

#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent), ui_(new Ui::Dialog)

{
  ui_->setupUi(this);
  //  ui_->widget->xAxis->setRange(-1 * ui_->e_f_1->value(),
  //  ui_->e_f_1->value());
  // ui_->widget->yAxis->setRange(-1 * ui_->e_f_2->value(),
  // ui_->e_f_2->value());
}

Dialog::~Dialog() { delete ui_; }
void Dialog::print_graph(std::string expression, QVector<double> x,
                         QVector<double> y) {
  expression_ = expression;
  ui_->widget->addGraph();
  ui_->widget->graph(0)->setData(x, y);
  ui_->widget->graph(0)->setPen(QColor(255, 0, 0, 255));
  // ui_->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
  ui_->widget->graph(0)->setLineStyle(QCPGraph::lsLine);
  ui_->widget->graph(0)->setScatterStyle(
      QCPScatterStyle(QCPScatterStyle::ssDot, 50));
  ui_->widget->xAxis->setRange(ui_->d_f_1->value(), ui_->d_f_2->value());
  ui_->widget->yAxis->setRange(ui_->e_f_1->value(), ui_->e_f_2->value());

  // ui_->widget->setInteraction(QCP::iRangeZoom, true);
  // ui_->widget->setInteraction(QCP::iRangeDrag, true);

  ui_->widget->replot();
}

void Dialog::on_d_f_1_valueChanged() { replot_graph(); }

void Dialog::on_d_f_2_valueChanged() { replot_graph(); }

void Dialog::on_e_f_1_valueChanged() { replot_graph(); }

void Dialog::on_e_f_2_valueChanged() { replot_graph(); }

void Dialog::on_e_f_3_valueChanged() { replot_graph(); }

void ::Dialog::replot_graph() {
  QVector<double> x, y;

  controller_->expr_to_graph(expression_, &x, &y, ui_->d_f_1->value(),
                             ui_->d_f_2->value(), ui_->e_f_1->value(),
                             ui_->e_f_2->value(), ui_->e_f_3->value());
  print_graph(expression_, x, y);
}
