#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#pragma once

#include <QMainWindow>
#include <QString>

#include "../controller/controller.h"
#include "dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  void setController(s21::Controller *controller) {
    this->controller_ = controller;
  }

private:
  Ui::MainWindow *ui_;
  s21::Controller *controller_;
  Dialog *graph_window_;
  void set_text(std::string str) noexcept;
  std::string get_text() noexcept;
  void makeConnections();
  bool check_x() noexcept;
  void plot_graph();
  void show_answer();
};
#endif // MAINWINDOW_H
