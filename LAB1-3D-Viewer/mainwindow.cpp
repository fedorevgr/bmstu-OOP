#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QMessageBox"
#include "QFileDialog"

#include "Geometry/ModelEntry.h"

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
void lineDrawer(SCALAR x1, SCALAR y1, SCALAR x2, SCALAR y2, void *args)
{
	static QGraphicsScene *scene;
	if (args)
		scene = (QGraphicsScene *) args;
	else if (scene)
		scene->addLine(x1, y1, x2, y2);;
}

static
void cleaningFunction(void *args)
{
	static QGraphicsScene *scene;
	if (args)
		scene = (QGraphicsScene *) args;
	else if (scene)
		scene->clear();
}


static
void
windowEventHandler(const Event event, const void *arg)
{
	ModelEC ec = process(event, arg);

	showError(ec);
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->graphicsView->setScene(new QGraphicsScene(this));

	const char *filename = nullptr;

    const QString qFilename = QFileDialog::getOpenFileName(this, "Open Object File", ".", "Text files (*.txt)");
	const QByteArray byteArray = qFilename.toUtf8();
	filename = byteArray.constData();

   	InitArgs initArgs;
	fillInitArgs(initArgs, filename, lineDrawer, cleaningFunction);

	lineDrawer(0, 0, 0, 0, this->ui->graphicsView->scene());
	cleaningFunction(this->ui->graphicsView->scene());

	windowEventHandler(INIT, &initArgs);
}

MainWindow::~MainWindow() {
	windowEventHandler(EXIT, NO_ARG);
    delete ui;
}

void MainWindow::on_posX_valueChanged(double arg1) {
    BASE3d newPos;
	set3Scalars(newPos, this->ui->posX->value(), this->ui->posY->value() * -1, this->ui->posZ->value());
	windowEventHandler(REPOS, &newPos);
}

void MainWindow::on_posY_valueChanged(double arg1) {
    BASE3d newPos;
	set3Scalars(newPos, this->ui->posX->value(), this->ui->posY->value()  * -1, this->ui->posZ->value());
	windowEventHandler(REPOS, &newPos);
}

void MainWindow::on_posZ_valueChanged(double arg1) {
    BASE3d newPos;
	set3Scalars(newPos, this->ui->posX->value(), this->ui->posY->value()  * -1, this->ui->posZ->value());
	windowEventHandler(REPOS, &newPos);
}

void MainWindow::on_rotX_valueChanged(double arg1) {
    BASE3d newPos;
	set3Scalars(newPos,
			degreeToRadians(this->ui->rotX->value()),
			degreeToRadians(this->ui->rotY->value()),
			degreeToRadians(this->ui->rotZ->value())
			);
	windowEventHandler(ROTATE, &newPos);
}

void MainWindow::on_rotY_valueChanged(double arg1) {
    BASE3d newPos;
	set3Scalars(newPos,
			degreeToRadians(this->ui->rotX->value()),
			degreeToRadians(this->ui->rotY->value()),
			degreeToRadians(this->ui->rotZ->value())
	);
	windowEventHandler(ROTATE, &newPos);
}

void MainWindow::on_rotZ_valueChanged(double arg1) {
    BASE3d newPos;
	set3Scalars(newPos,
			degreeToRadians(this->ui->rotX->value()),
			degreeToRadians(this->ui->rotY->value()),
			degreeToRadians(this->ui->rotZ->value())
	);
	windowEventHandler(ROTATE, &newPos);
}

void MainWindow::on_scaleX_valueChanged(double arg1) {
    BASE3d newPos;
	set3Scalars(newPos, this->ui->scaleX->value(), this->ui->scaleY->value(), this->ui->scaleZ->value());
	windowEventHandler(SCALE, &newPos);
}

void MainWindow::on_scaleY_valueChanged(double arg1) {
    BASE3d newPos;
	set3Scalars(newPos, this->ui->scaleX->value(), this->ui->scaleY->value(), this->ui->scaleZ->value());
	windowEventHandler(SCALE, &newPos);
}

void MainWindow::on_scaleZ_valueChanged(double arg1) {
    BASE3d newPos;
	set3Scalars(newPos, this->ui->scaleX->value(), this->ui->scaleY->value(), this->ui->scaleZ->value());
	windowEventHandler(SCALE, &newPos);
}
