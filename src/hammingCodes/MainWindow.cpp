#include "MainWindow.h"

MainWindow::MainWindow() {
    setWindowTitle("Коды Хэмминга");

    createMenuBar();

    mainWidget = new HammingLabWidget();
    setCentralWidget(mainWidget);

    connect(mainWidget, SIGNAL(statusInfo(QString)), this, SLOT(onStatusMessage(QString)));
    statusBar()->showMessage("Ready");
}

void MainWindow::onStatusMessage(QString message) {
    statusBar()->showMessage(message);
}

void MainWindow::openAboutMenu() {
    AboutWindow aboutWindow;

    setEnabled(false);
    aboutWindow.exec();
    setEnabled(true);
}

void MainWindow::createMenuBar() {
    QAction *openAboutMenu = new QAction("О программе", this);
    connect(openAboutMenu, SIGNAL(triggered()), this, SLOT(openAboutMenu()));

    QMenu *fileMenu = menuBar()->addMenu("Файл");
    fileMenu->addAction(openAboutMenu);
}
