#include "mainwindow.h"
#include <QApplication>
#include <QSurfaceFormat>
#include <iostream>

int main(int argc, char *argv[])
{
    /*OpenGL format must be set before launching application*/
    QSurfaceFormat format;
    format.setVersion(4,1);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);

    if (argc != 5) {
        std::cout << "Usage: ./terrain "
                     "{funky|plane|curve} "
                     "{resolution} "
                     "{size of field} "
                     "{1 for gradient normals, 0 for face normals}" << std::endl;
        return -1;
    }
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
