#include "mainwindow.h"
#include "./ui_mainwindow.h"

#define DEFAULT_FILE "abc.txt"

typedef enum Event_
{
	INIT,
	REPOS,
	ROTATE,
	SCALE,
	EXIT
} Event;

const void *NO_ARG = nullptr;

static
void
process(const Event event, const void *arg)
{
	static Model *model = nullptr;
	ModelEC modelEc = MODEL_OK;

	switch (event)
	{
	case INIT:
		modelEc = modelFromFile(DEFAULT_FILE, &model);
		break;
	case REPOS:
		break;
	case ROTATE:
		break;
	case SCALE:
		break;
	case EXIT:
		break;
	}

	// handle ec
}

MainWindow::MainWindow(QWidget *parent, Model *model)
		: QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	process(INIT, NO_ARG);
	ui->graphicsView->setScene(new QGraphicsScene(this));
	ui->graphicsView->scene()->addEllipse(-100, -100, 100, 100);
	ui->graphicsView->scene()->addEllipse(200, 200, 100, 100);
	ui->graphicsView->scene()->addEllipse(0, 0, 6, 6);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_posX_valueChanged(double arg1)
{
	_3DBASE_ newPos;
	init3Scalars(&newPos, arg1, 0, 0);
}

void MainWindow::on_posY_valueChanged(double arg1)
{
	_3DBASE_ newPos;
	init3Scalars(&newPos, 0, arg1, 0);
}

void MainWindow::on_posZ_valueChanged(double arg1)
{
	_3DBASE_ newPos;
	init3Scalars(&newPos, 0, 0, arg1);
}

void MainWindow::on_rotX_valueChanged(double arg1)
{
}

void MainWindow::on_rotY_valueChanged(double arg1)
{
}

void MainWindow::on_rotZ_valueChanged(double arg1)
{
}

void MainWindow::on_scaleX_valueChanged(double arg1)
{
}

void MainWindow::on_scaleY_valueChanged(double arg1)
{
}

void MainWindow::on_scaleZ_valueChanged(double arg1)
{
}
