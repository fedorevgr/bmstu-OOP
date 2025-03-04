#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QMessageBox"
#include "QFileDialog"

#include "Handle/ModelHandler.h"
#include "GraphicsImpl/GraphicsImpl.h"

static inline BASE3d gatherPosition(Ui_MainWindow &ui);
static inline BASE3d gatherRotation(Ui_MainWindow &ui);
static inline BASE3d gatherScale(Ui_MainWindow &ui);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->graphicsView->setScene(new QGraphicsScene(this));

	lineDrawer({0}, {0}, this->ui->graphicsView->scene());
	cleaningFunction(this->ui->graphicsView->scene());

	Request request;

    const QString qFilename = QFileDialog::getOpenFileName(this, "Open Model File", ".", "Text files (*.txt)");
	const QByteArray byteArray = qFilename.toUtf8();
	request.filename = byteArray.constData();

	handle(INIT, request, createCanvasTools(lineDrawer, cleaningFunction), showError);
}

MainWindow::~MainWindow() {
	handle(EXIT, EMPTY_REQ, createCanvasTools(nullptr, nullptr), showError);
    delete ui;
}

void MainWindow::on_posX_valueChanged(double arg1) {
	Request request;
	request.transform = gatherPosition(*this->ui);
	handle(REPOS, request, createCanvasTools(lineDrawer, cleaningFunction), showError);
}

void MainWindow::on_posY_valueChanged(double arg1) {
	Request request;
	request.transform = gatherPosition(*this->ui);
	handle(REPOS, request, createCanvasTools(lineDrawer, cleaningFunction), showError);
}

void MainWindow::on_posZ_valueChanged(double arg1) {
	Request request;
	request.transform = gatherPosition(*this->ui);
	handle(REPOS, request, createCanvasTools(lineDrawer, cleaningFunction), showError);
}

void MainWindow::on_rotX_valueChanged(double arg1) {
	Request request;
    request.transform = gatherRotation(*this->ui);
	handle(ROTATE, request, createCanvasTools(lineDrawer, cleaningFunction), showError);
}

void MainWindow::on_rotY_valueChanged(double arg1) {
	Request request;
	request.transform = gatherRotation(*this->ui);
	handle(ROTATE, request, createCanvasTools(lineDrawer, cleaningFunction), showError);
}

void MainWindow::on_rotZ_valueChanged(double arg1) {
	Request request;
	request.transform = gatherRotation(*this->ui);
	handle(ROTATE, request, createCanvasTools(lineDrawer, cleaningFunction), showError);
}

void MainWindow::on_scaleX_valueChanged(double arg1) {
	Request request;
	request.transform = gatherScale(*this->ui);
	handle(SCALE, request, createCanvasTools(lineDrawer, cleaningFunction), showError);
}

void MainWindow::on_scaleY_valueChanged(double arg1) {
	Request request;
	request.transform = gatherScale(*this->ui);
	handle(SCALE, request, createCanvasTools(lineDrawer, cleaningFunction), showError);
}

void MainWindow::on_scaleZ_valueChanged(double arg1) {
	Request request;
	request.transform = gatherScale(*this->ui);
	handle(SCALE, request, createCanvasTools(lineDrawer, cleaningFunction), showError);
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

