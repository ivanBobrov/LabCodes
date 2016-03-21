#include <QApplication>
#include <QWidget>

#include "MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);

    /*CyclicCodesLab model;
    model.setNumberOfThreadsToUse(4);

    CyclicCodesWidget widget(model);
    widget.show();*/

    MainWindow mainWindow;
    mainWindow.show();

    return application.exec();
}