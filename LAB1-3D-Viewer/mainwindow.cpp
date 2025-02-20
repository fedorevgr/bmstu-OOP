#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QMessageBox"
#include "QFileDialog"

#define DEFAULT_FILE "abc.txt"

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
showError(const ModelEC modelEc) {
    switch (modelEc) {
        case MODEL_FILE_ERROR:
            QMessageBox::critical(nullptr, "Error", "File error, figure can't be shown");
        break;
        case MODEL_UNKNOWN_ERROR:
            QMessageBox::critical(nullptr, "Error", "Unknown error");
        break;
        case  MODEL_MEMORY_ERROR:
            QMessageBox::critical(nullptr, "Error", "Memory error, figure can't be shown");
        break;
        case MODEL_ARG_ERROR:
            QMessageBox::critical(nullptr, "Error", "Arg error");
        break;
        default:
            break;
    }
}

static
void
process(const Event event, const void *arg) {
    static Model model;
    static QGraphicsScene *scene;

    BASE3d *newPos, *newRotation, *newScale;

    ModelEC modelEc = MODEL_OK;

    switch (event) {
        case INIT:
            modelEc = initModel((const char *) ((void **) arg)[1], model);
            scene = (QGraphicsScene *) ((void **) arg)[0];
            break;
        case REPOS:
            newPos = (BASE3d *) arg;
			modelSetPos(model, *newPos);
            break;
        case ROTATE:
            newRotation = (BASE3d *) arg;
			modelSetRot(model, *newRotation);
            break;
        case SCALE:
            newScale = (BASE3d *) arg;
			modelSetScale(model, *newScale);
            break;
        case EXIT:
            modelFree(model);
            break;
    }

    if (event != EXIT && modelEc == MODEL_OK)
	{
		scene->clear();
		modelDraw(model, *scene);
	}

    showError(modelEc);
}

static
const char *
getFilename(const QString &qString) {
    const char *fileName = nullptr;

    if (!qString.isEmpty()) {
        const QByteArray byteArray = qString.toUtf8();
        fileName = byteArray.constData();
    }

    return fileName;
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->graphicsView->setScene(new QGraphicsScene(this));

    const QString qFilename = QFileDialog::getOpenFileName(this, "Open File", "");
    void *initArgs[2] = { ui->graphicsView->scene(), (void *) getFilename(qFilename) };

    process(INIT, initArgs);
}

MainWindow::~MainWindow() {
    process(EXIT, NO_ARG);
    delete ui;
}

void MainWindow::on_posX_valueChanged(double arg1) {
    BASE3d newPos;
	set3Scalars(newPos, this->ui->posX->value(), this->ui->posY->value(), this->ui->posZ->value());
    process(REPOS, &newPos);
}

void MainWindow::on_posY_valueChanged(double arg1) {
    BASE3d newPos;
	set3Scalars(newPos, this->ui->posX->value(), this->ui->posY->value(), this->ui->posZ->value());
    process(REPOS, &newPos);
}

void MainWindow::on_posZ_valueChanged(double arg1) {
    BASE3d newPos;
	set3Scalars(newPos, this->ui->posX->value(), this->ui->posY->value(), this->ui->posZ->value());
    process(REPOS, &newPos);
}

void MainWindow::on_rotX_valueChanged(double arg1) {
    BASE3d newPos;
	set3Scalars(newPos,
			degreeToRadians(this->ui->rotX->value()),
			degreeToRadians(this->ui->rotY->value()),
			degreeToRadians(this->ui->rotZ->value())
			);
    process(ROTATE, &newPos);
}

void MainWindow::on_rotY_valueChanged(double arg1) {
    BASE3d newPos;
	set3Scalars(newPos,
			degreeToRadians(this->ui->rotX->value()),
			degreeToRadians(this->ui->rotY->value()),
			degreeToRadians(this->ui->rotZ->value())
	);
    process(ROTATE, &newPos);
}

void MainWindow::on_rotZ_valueChanged(double arg1) {
    BASE3d newPos;
	set3Scalars(newPos,
			degreeToRadians(this->ui->rotX->value()),
			degreeToRadians(this->ui->rotY->value()),
			degreeToRadians(this->ui->rotZ->value())
	);
    process(ROTATE, &newPos);
}

void MainWindow::on_scaleX_valueChanged(double arg1) {
    BASE3d newPos;
	set3Scalars(newPos, this->ui->scaleX->value(), this->ui->scaleY->value(), this->ui->scaleZ->value());
    process(SCALE, &newPos);
}

void MainWindow::on_scaleY_valueChanged(double arg1) {
    BASE3d newPos;
	set3Scalars(newPos, this->ui->scaleX->value(), this->ui->scaleY->value(), this->ui->scaleZ->value());
    process(SCALE, &newPos);
}

void MainWindow::on_scaleZ_valueChanged(double arg1) {
    BASE3d newPos;
	set3Scalars(newPos, this->ui->scaleX->value(), this->ui->scaleY->value(), this->ui->scaleZ->value());
    process(SCALE, &newPos);
}
