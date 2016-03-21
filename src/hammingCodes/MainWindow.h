#ifndef HAMMING_CODES_MAIN_WINDOW_H
#define HAMMING_CODES_MAIN_WINDOW_H

#include <QtWidgets>
#include "HammingLabWidget.h"
#include "AboutWindow.h"

class MainWindow : public QMainWindow {

Q_OBJECT

public:
    MainWindow();

public slots:
    void onStatusMessage(QString message);
    void openAboutMenu();

private:
    HammingLabWidget *mainWidget;

    void createMenuBar();
};


#endif //HAMMINGC_ODES_MAIN_WINDOW_H
