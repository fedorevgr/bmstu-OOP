#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->graphicsView->setScene(new QGraphicsScene(this));
    ui->graphicsView->scene()->addEllipse(-100, -100, 100, 100);
    ui->graphicsView->scene()->addEllipse(200, 200, 100, 100);
    ui->graphicsView->scene()->addEllipse(0, 0, 6, 6);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_posX_valueChanged(double arg1) {
    printf("%lf\n", arg1);
}

void MainWindow::on_posY_valueChanged(double arg1) {
}

void MainWindow::on_posZ_valueChanged(double arg1) {
}

void MainWindow::on_rotX_valueChanged(double arg1) {
}

void MainWindow::on_rotY_valueChanged(double arg1) {
}

void MainWindow::on_rotZ_valueChanged(double arg1) {
}

void MainWindow::on_scaleX_valueChanged(double arg1) {
}

void MainWindow::on_scaleY_valueChanged(double arg1) {
}

void MainWindow::on_scaleZ_valueChanged(double arg1) {
}
