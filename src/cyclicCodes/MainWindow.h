#ifndef HAMMING_CODES_MAIN_WINDOW_H
#define HAMMING_CODES_MAIN_WINDOW_H

#include <QtWidgets>
#include "CyclicCodesWidget.h"
#include "CyclicCodesLab.h"
#include "AboutWindow.h"

class MainWindow : public QMainWindow {

Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

public slots:
    void openAboutMenu();
    void infoMessage(QString message);

private:
    static const int THREADS_TO_USE = 3;

    CyclicCodesLab *codesLab;
    CyclicCodesWidget *mainWidget;

    void createMenuBar();
};


#endif //HAMMING_CODES_MAIN_WINDOW_H
