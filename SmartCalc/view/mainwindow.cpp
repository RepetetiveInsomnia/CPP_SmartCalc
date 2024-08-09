#include "mainwindow.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow) {
  ui_->setupUi(this);
  makeConnections();
}

MainWindow::~MainWindow() { delete ui_; }

void MainWindow::makeConnections() {
  connect(ui_->pushButton_0, &QPushButton::clicked, this,
          [this]() { MainWindow::set_text("0"); });
  connect(ui_->pushButton_1, &QPushButton::clicked, this,
          [this]() { MainWindow::set_text("1"); });
  connect(ui_->pushButton_2, &QPushButton::clicked, this,
          [this]() { MainWindow::set_text("2"); });
  connect(ui_->pushButton_3, &QPushButton::clicked, this,
          [this]() { MainWindow::set_text("3"); });
  connect(ui_->pushButton_4, &QPushButton::clicked, this,
          [this]() { MainWindow::set_text("4"); });
  connect(ui_->pushButton_5, &QPushButton::clicked, this,
          [this]() { MainWindow::set_text("5"); });
  connect(ui_->pushButton_6, &QPushButton::clicked, this,
          [this]() { MainWindow::set_text("6"); });
  connect(ui_->pushButton_7, &QPushButton::clicked, this,
          [this]() { MainWindow::set_text("7"); });
  connect(ui_->pushButton_8, &QPushButton::clicked, this,
          [this]() { MainWindow::set_text("8"); });
  connect(ui_->pushButton_9, &QPushButton::clicked, this,
          [this]() { MainWindow::set_text("9"); });
  connect(ui_->pushButton_dot, &QPushButton::clicked, this,
          [this]() { MainWindow::set_text("."); });
  connect(ui_->pushButton_plus, &QPushButton::clicked, this, [this]() {
    MainWindow::set_text(controller_->line_update(s21::Operations::ADD));
  });
  connect(ui_->pushButton_minus, &QPushButton::clicked, this, [this]() {
    MainWindow::set_text(controller_->line_update(s21::Operations::SUB));
  });
  connect(ui_->pushButton_pow, &QPushButton::clicked, this, [this]() {
    MainWindow::set_text(controller_->line_update(s21::Operations::POW));
  });
  connect(ui_->pushButton_umn, &QPushButton::clicked, this, [this]() {
    MainWindow::set_text(controller_->line_update(s21::Operations::MUL));
  });
  connect(ui_->pushButton_del, &QPushButton::clicked, this, [this]() {
    MainWindow::set_text(controller_->line_update(s21::Operations::DIV));
  });
  connect(ui_->pushButton_cos, &QPushButton::clicked, this, [this]() {
    MainWindow::set_text(controller_->line_update(s21::Operations::COS));
  });
  connect(ui_->pushButton_sin, &QPushButton::clicked, this, [this]() {
    MainWindow::set_text(controller_->line_update(s21::Operations::SIN));
  });
  connect(ui_->pushButton_tan, &QPushButton::clicked, this, [this]() {
    MainWindow::set_text(controller_->line_update(s21::Operations::TAN));
  });
  connect(ui_->pushButton_acos, &QPushButton::clicked, this, [this]() {
    MainWindow::set_text(controller_->line_update(s21::Operations::ACOS));
  });
  connect(ui_->pushButton_asin, &QPushButton::clicked, this, [this]() {
    MainWindow::set_text(controller_->line_update(s21::Operations::ASIN));
  });
  connect(ui_->pushButton_atan, &QPushButton::clicked, this, [this]() {
    MainWindow::set_text(controller_->line_update(s21::Operations::ATAN));
  });
  connect(ui_->pushButton_ln, &QPushButton::clicked, this, [this]() {
    MainWindow::set_text(controller_->line_update(s21::Operations::LN));
  });
  connect(ui_->pushButton_log, &QPushButton::clicked, this, [this]() {
    MainWindow::set_text(controller_->line_update(s21::Operations::LOG));
  });
  connect(ui_->pushButton_sqrt, &QPushButton::clicked, this, [this]() {
    MainWindow::set_text(controller_->line_update(s21::Operations::SQRT));
  });
  connect(ui_->pushButton_mod, &QPushButton::clicked, this, [this]() {
    MainWindow::set_text(controller_->line_update(s21::Operations::MOD));
  });
  connect(ui_->pushButton_AC, &QPushButton::clicked, this,
          [this]() { ui_->lineEdit->setText(ui_->lineEdit->text() = ""); });
  connect(ui_->pushButton_x, &QPushButton::clicked, this, [this]() {
    MainWindow::set_text(controller_->line_update(s21::Operations::X));
  });
  connect(ui_->pushButton_Os, &QPushButton::clicked, this, [this]() {
    MainWindow::set_text(controller_->line_update(s21::Operations::OP_BRACKET));
  });
  connect(ui_->pushButton_Cs, &QPushButton::clicked, this, [this]() {
    MainWindow::set_text(controller_->line_update(s21::Operations::CL_BRACKET));
  });
  connect(ui_->pushButton_end, &QPushButton::clicked, this, [this]() {
    if (this->check_x() == true) {
      this->show_answer();
    } else {
      this->plot_graph();
    }
  });
}

void MainWindow::set_text(std::string str) noexcept {
  ui_->lineEdit->setText(ui_->lineEdit->text() + QString::fromStdString(str));
}
bool MainWindow::check_x() noexcept {
  return controller_->check_x(this->get_text());
}

void MainWindow::show_answer() {
  try {
    QString numberResult =
        QString::number(controller_->expr_to_model(this->get_text()));
    ui_->lineEdit->setText(ui_->lineEdit->text() = "");
    ui_->lineEdit->setText(numberResult);
  } catch (const s21::MathException &e) {
    ui_->lineEdit->setText(ui_->lineEdit->text() = "");
    this->set_text(e.what());
  }
}
void MainWindow::plot_graph() {
  QVector<double> x, y;
  try {
    controller_->expr_to_graph(this->get_text(), &x, &y, -10, 10, -10, 10,
                               5000);

    graph_window_ = new Dialog(this);
    graph_window_->setModal(true);
    graph_window_->print_graph(this->get_text(), x, y);
    graph_window_->show();
  } catch (const s21::MathException &e) {
    ui_->lineEdit->setText(ui_->lineEdit->text() = "");
    this->set_text(e.what());
  }
}

std::string MainWindow::get_text() noexcept {
  return ui_->lineEdit->text().toStdString();
}
