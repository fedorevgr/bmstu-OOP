#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    for (int i = 0; i < argc; i++)
        printf("%s\n", argv[i]);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

