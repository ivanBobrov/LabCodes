#include <QApplication>
#include <QWidget>

#include "MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    return application.exec();
}