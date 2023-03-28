#include "mainwindow.h"

#include <QApplication>

#ifdef VLD_MODULE
    #include "vld.h"
#endif

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
