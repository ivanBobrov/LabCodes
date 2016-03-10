#include <QApplication>
#include <QWidget>

#include "CyclicCodesWidget.h"
#include "CyclicCodesLab.h"

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);

    CyclicCodesLab model;
    CyclicCodesWidget widget(model);

    model.setCyclicLabView(widget);
    widget.show();

    return application.exec();
}