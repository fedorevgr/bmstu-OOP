#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QMessageBox"
#include "QFileDialog"

#include "ModelHandler.h"

// todo repeat
// todo static
// todo poitt draw
static
void
showError(const ModelEC modelEc)
{
	const char *msg = nullptr;
	switch (modelEc)
	{
		case MODEL_FILE_ERROR:
			msg = "File error, figure can't be shown";
			break;
		case MODEL_UNKNOWN_ERROR:
			msg = "Unknown error";
		break;
		case MODEL_MEMORY_ERROR:
			msg = "Memory error, figure can't be shown";
		break;
		case MODEL_ARG_ERROR:
			msg = "Arg error, figure can't be shown";
		break;
		default:
			break;
	}
	if (msg)
		QMessageBox::critical(nullptr, "Error", msg);
}

static
void lineDrawer(Point p1, Point p2, void *args)
{
	static QGraphicsScene *scene;
	if (args)
		scene = (QGraphicsScene *) args;
	else if (scene)
		scene->addLine(p1.x, p1.y, p2.x, p2.y);
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


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->graphicsView->setScene(new QGraphicsScene(this));

	const char *filename = nullptr;

    const QString qFilename = QFileDialog::getOpenFileName(this, "Open Model File", ".", "Text files (*.txt)");
	const QByteArray byteArray = qFilename.toUtf8();
	filename = byteArray.constData();

	lineDrawer({0}, {0}, this->ui->graphicsView->scene());
	cleaningFunction(this->ui->graphicsView->scene());

	modelHandle(INIT, filename, lineDrawer, cleaningFunction, showError);
}

MainWindow::~MainWindow() {
	modelHandle(EXIT, NO_ARG, nullptr, nullptr, showError);
    delete ui;
}

void MainWindow::on_posX_valueChanged(double arg1) {
	BASE3d newPos = gatherPosition(*this->ui);
	modelHandle(REPOS, &newPos, lineDrawer, cleaningFunction, showError);
}

void MainWindow::on_posY_valueChanged(double arg1) {
	BASE3d newPos = gatherPosition(*this->ui);
	modelHandle(REPOS, &newPos,lineDrawer, cleaningFunction,  showError);
}

void MainWindow::on_posZ_valueChanged(double arg1) {
	BASE3d newPos = gatherPosition(*this->ui);
	modelHandle(REPOS, &newPos,lineDrawer, cleaningFunction,  showError);
}

void MainWindow::on_rotX_valueChanged(double arg1) {
    BASE3d newPos = gatherRotation(*this->ui);
	modelHandle(ROTATE, &newPos, lineDrawer, cleaningFunction, showError);
}

void MainWindow::on_rotY_valueChanged(double arg1) {
	BASE3d newPos = gatherRotation(*this->ui);
	modelHandle(ROTATE, &newPos,lineDrawer, cleaningFunction,  showError);
}

void MainWindow::on_rotZ_valueChanged(double arg1) {
	BASE3d newPos = gatherRotation(*this->ui);
	modelHandle(ROTATE, &newPos, lineDrawer, cleaningFunction, showError);
}

void MainWindow::on_scaleX_valueChanged(double arg1) {
	BASE3d newPos = gatherScale(*this->ui);
	modelHandle(SCALE, &newPos, lineDrawer, cleaningFunction, showError);
}

void MainWindow::on_scaleY_valueChanged(double arg1) {
	BASE3d newPos = gatherScale(*this->ui);
	modelHandle(SCALE, &newPos, lineDrawer, cleaningFunction, showError);
}

void MainWindow::on_scaleZ_valueChanged(double arg1) {
    BASE3d newPos = gatherScale(*this->ui);
	modelHandle(SCALE, &newPos, lineDrawer, cleaningFunction,  showError);
}
