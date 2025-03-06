#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QFileDialog"

#include "Handle/ModelHandler.h"
#include "GraphicsImpl/GraphicsImpl.h"

static void onTransform(Ui_MainWindow &ui, Event);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->graphicsView->setScene(new QGraphicsScene(this));

    ScreenTools screenTools = composeTools(lineDrawer, this->ui->graphicsView->scene(),
			cleaningFunction, this->ui->graphicsView->scene());

    const QString qFilename = QFileDialog::getOpenFileName(this, "Open Model File", ".", "Text files (*.txt)");
    const QByteArray byteArray = qFilename.toUtf8();
    const char *filename = byteArray.constData();

    const Request request = composeRequest(INIT, filename, ZERO_BASE, screenTools, showError);
    handle(request);
}

MainWindow::~MainWindow() {
    handle(EMPTY_REQ);
    delete ui;
}

void MainWindow::on_posX_valueChanged(double arg1) {    onTransform(*this->ui, REPOS);}

void MainWindow::on_posY_valueChanged(double arg1) {    onTransform(*this->ui, REPOS);}

void MainWindow::on_posZ_valueChanged(double arg1) {    onTransform(*this->ui, REPOS);}

void MainWindow::on_rotX_valueChanged(double arg1) {    onTransform(*this->ui, ROTATE);}

void MainWindow::on_rotY_valueChanged(double arg1) {    onTransform(*this->ui, ROTATE);}

void MainWindow::on_rotZ_valueChanged(double arg1) { onTransform(*this->ui, ROTATE); }

void MainWindow::on_scaleX_valueChanged(double arg1) { onTransform(*this->ui, SCALE); }

void MainWindow::on_scaleY_valueChanged(double arg1) { onTransform(*this->ui, SCALE); }

void MainWindow::on_scaleZ_valueChanged(double arg1) { onTransform(*this->ui, SCALE); }


static inline
BASE3d
gatherPosition(Ui_MainWindow &ui) {
    BASE3d newPos;
    set3Scalars(newPos, ui.posX->value(), ui.posY->value() * -1, ui.posZ->value());
    return newPos;
}

static inline
BASE3d
gatherRotation(Ui_MainWindow &ui) {
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
gatherScale(Ui_MainWindow &ui) {
    BASE3d newPos;
    set3Scalars(newPos, ui.scaleX->value(), ui.scaleY->value(), ui.scaleZ->value());
    return newPos;
}

static
void
onTransform(Ui_MainWindow &ui, const Event type) {
    if (type != REPOS && type != ROTATE && type != SCALE)
        return;

    BASE3d transform;

    switch (type) {
        case REPOS: transform = gatherPosition(ui);
            break;
        case ROTATE: transform = gatherRotation(ui);
            break;
        case SCALE: transform = gatherScale(ui);
            break;
        default: break;
    }

    ScreenTools screenTools = composeTools(lineDrawer, ui.graphicsView->scene(),
			cleaningFunction, ui.graphicsView->scene());

    const Request request = composeRequest(type, nullptr, transform, screenTools, showError);
    handle(request);
}
