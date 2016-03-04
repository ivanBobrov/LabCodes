#include <QApplication>
#include <QWidget>

#include "CyclicCodesWidget.h"
#include "CyclicCodesLab.h"

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);

    CyclicCodesWidget widget;
    CyclicCodesLab model(widget);
    widget.show();

    return application.exec();
}