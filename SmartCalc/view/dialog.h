#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QMainWindow>
#include <QPixmap>
#include <QPrinter>
#include <QString>
#include <QVector>

#include "../controller/controller.h"
#include "../qcustomplot.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog {
  Q_OBJECT

public:
  explicit Dialog(QWidget *parent = nullptr);
  ~Dialog();
  void print_graph(std::string expression, QVector<double> x,
                   QVector<double> y);
private slots:
  void on_d_f_1_valueChanged();
  void on_d_f_2_valueChanged();
  void on_e_f_1_valueChanged();
  void on_e_f_2_valueChanged();
  void on_e_f_3_valueChanged();

private:
  Ui::Dialog *ui_;
  s21::Controller *controller_;
  std::string expression_;
  void replot_graph();
};

#endif // DIALOG_H
