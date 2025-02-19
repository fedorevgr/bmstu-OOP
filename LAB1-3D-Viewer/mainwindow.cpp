#include "mainwindow.h"
#include "./ui_mainwindow.h"

#define DEFAULT_FILE "..\\..\\abc.txt"

typedef enum Event_ {
    INIT,
    REPOS,
    ROTATE,
    SCALE,
    EXIT
} Event;

const void *NO_ARG = nullptr;

static
void
process(const Event event, const void *arg) {
    static Model model = { nullptr };
    static QGraphicsScene *scene;

    BASE3d *newPos, *newRotation, *newScale;

    ModelEC modelEc = MODEL_OK;

    switch (event) {
        case INIT:
            // init model
            initModel(DEFAULT_FILE, model);
            scene = (QGraphicsScene *) arg;
            break;
        case REPOS:
            // set new coordinates
            newPos = (BASE3d *) arg;
            printf("New pos: %lf, %lf, %lf\n", newPos->x, newPos->y, newPos->z);
            break;
        case ROTATE:
            // set new rotation
            newRotation = (BASE3d *) arg;

            break;
        case SCALE:
            // set new scale
            newScale = (BASE3d *) arg;

            break;
        case EXIT:
            // model free
            modelFree(model);
            break;
    }

    if (event != EXIT) {
        scene->addEllipse(-100, -100, 100, 100);
    }

    // handle ec
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->graphicsView->setScene(new QGraphicsScene(this));

    process(INIT, (void *) ui->graphicsView->scene());
    ui->graphicsView->scene()->addEllipse(200, 200, 100, 100);
    ui->graphicsView->scene()->addEllipse(0, 0, 6, 6);
}

MainWindow::~MainWindow() {
    process(EXIT, NO_ARG);
    delete ui;
}

void MainWindow::on_posX_valueChanged(double arg1) {
    BASE3d newPos;
    init3Scalars(newPos, this->ui->posX->value(), this->ui->posY->value(), this->ui->posZ->value());
    process(REPOS, &newPos);
}

void MainWindow::on_posY_valueChanged(double arg1) {
    BASE3d newPos;
    init3Scalars(newPos, this->ui->posX->value(), this->ui->posY->value(), this->ui->posZ->value());
    process(REPOS, &newPos);
}

void MainWindow::on_posZ_valueChanged(double arg1) {
    BASE3d newPos;
    init3Scalars(newPos, this->ui->posX->value(), this->ui->posY->value(), this->ui->posZ->value());
    process(REPOS, &newPos);
}

void MainWindow::on_rotX_valueChanged(double arg1) {
    BASE3d newPos;
    init3Scalars(newPos, this->ui->rotX->value(), this->ui->rotY->value(), this->ui->rotZ->value());
    process(ROTATE, &newPos);
}

void MainWindow::on_rotY_valueChanged(double arg1) {
    BASE3d newPos;
    init3Scalars(newPos, this->ui->rotX->value(), this->ui->rotY->value(), this->ui->rotZ->value());
    process(ROTATE, &newPos);
}

void MainWindow::on_rotZ_valueChanged(double arg1) {
    BASE3d newPos;
    init3Scalars(newPos, this->ui->rotX->value(), this->ui->rotY->value(), this->ui->rotZ->value());
    process(ROTATE, &newPos);
}

void MainWindow::on_scaleX_valueChanged(double arg1) {
    BASE3d newPos;
    init3Scalars(newPos, this->ui->scaleX->value(), this->ui->scaleY->value(), this->ui->scaleZ->value());
    process(SCALE, &newPos);
}

void MainWindow::on_scaleY_valueChanged(double arg1) {
    BASE3d newPos;
    init3Scalars(newPos, this->ui->scaleX->value(), this->ui->scaleY->value(), this->ui->scaleZ->value());
    process(SCALE, &newPos);
}

void MainWindow::on_scaleZ_valueChanged(double arg1) {
    BASE3d newPos;
    init3Scalars(newPos, this->ui->scaleX->value(), this->ui->scaleY->value(), this->ui->scaleZ->value());
    process(SCALE, &newPos);
}
