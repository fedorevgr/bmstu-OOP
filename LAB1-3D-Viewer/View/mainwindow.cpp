#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QMessageBox"
#include "QFileDialog"

#include "ModelHandler.h"
#include "GraphicsImpl/GraphicsImpl.h"

static inline BASE3d gatherPosition(Ui_MainWindow &ui);
static inline BASE3d gatherRotation(Ui_MainWindow &ui);
static inline BASE3d gatherScale(Ui_MainWindow &ui);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->graphicsView->setScene(new QGraphicsScene(this));

	Request request;

    const QString qFilename = QFileDialog::getOpenFileName(this, "Open Model File", ".", "Text files (*.txt)");
	const QByteArray byteArray = qFilename.toUtf8();
	request.filename = byteArray.constData();

	lineDrawer({0}, {0}, this->ui->graphicsView->scene());
	cleaningFunction(this->ui->graphicsView->scene());

	modelHandle(INIT, request, lineDrawer, cleaningFunction, showError);
}

MainWindow::~MainWindow() {
	modelHandle(EXIT, EMPTY_REQ, nullptr, nullptr, showError);
    delete ui;
}

void MainWindow::on_posX_valueChanged(double arg1) {
	Request request;
	request.transform = gatherPosition(*this->ui);
	modelHandle(REPOS, request, lineDrawer, cleaningFunction, showError);
}

void MainWindow::on_posY_valueChanged(double arg1) {
	Request request;
	request.transform = gatherPosition(*this->ui);
	modelHandle(REPOS, request, lineDrawer, cleaningFunction, showError);
}

void MainWindow::on_posZ_valueChanged(double arg1) {
	Request request;
	request.transform = gatherPosition(*this->ui);
	modelHandle(REPOS, request, lineDrawer, cleaningFunction, showError);
}

void MainWindow::on_rotX_valueChanged(double arg1) {
	Request request;
    request.transform = gatherRotation(*this->ui);
	modelHandle(ROTATE, request, lineDrawer, cleaningFunction, showError);
}

void MainWindow::on_rotY_valueChanged(double arg1) {
	Request request;
	request.transform = gatherRotation(*this->ui);
	modelHandle(ROTATE, request, lineDrawer, cleaningFunction, showError);
}

void MainWindow::on_rotZ_valueChanged(double arg1) {
	Request request;
	request.transform = gatherRotation(*this->ui);
	modelHandle(ROTATE, request, lineDrawer, cleaningFunction, showError);
}

void MainWindow::on_scaleX_valueChanged(double arg1) {
	Request request;
	request.transform = gatherScale(*this->ui);
	modelHandle(SCALE, request, lineDrawer, cleaningFunction, showError);
}

void MainWindow::on_scaleY_valueChanged(double arg1) {
	Request request;
	request.transform = gatherScale(*this->ui);
	modelHandle(SCALE, request, lineDrawer, cleaningFunction, showError);
}

void MainWindow::on_scaleZ_valueChanged(double arg1) {
	Request request;
	request.transform = gatherScale(*this->ui);
	modelHandle(SCALE, request, lineDrawer, cleaningFunction, showError);
}


static inline
BASE3d
gatherPosition(Ui_MainWindow &ui)
{
	BASE3d newPos;
	set3Scalars(newPos, ui.posX->value(), ui.posY->value()  * -1, ui.posZ->value());
	return newPos;
}

static inline
BASE3d
gatherRotation(Ui_MainWindow &ui)
{
	BASE3d newPos;
	set3Scalars(newPos,
			degreeToRadians(ui.rotX->value()),
			degreeToRadians(ui.rotY->value()),
			degreeToRadians(ui.rotZ->value())
	);
	return newPos;
}

static inline
BASE3d
gatherScale(Ui_MainWindow &ui)
{
	BASE3d newPos;
	set3Scalars(newPos, ui.scaleX->value(), ui.scaleY->value(), ui.scaleZ->value());
	return newPos;
}

