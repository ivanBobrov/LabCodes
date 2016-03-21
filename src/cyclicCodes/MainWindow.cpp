#include "MainWindow.h"

MainWindow::MainWindow() {
    statusBar()->showMessage("Запуск");
    createMenuBar();

    codesLab = new CyclicCodesLab;
    codesLab->setNumberOfThreadsToUse(THREADS_TO_USE);
    mainWidget = new CyclicCodesWidget(*codesLab);
    setCentralWidget(mainWidget);

    statusBar()->showMessage("Готово");
    connect(mainWidget, SIGNAL(statusInformation(QString)), this, SLOT(infoMessage(QString)));
}

MainWindow::~MainWindow() {
    delete codesLab;
}

void MainWindow::createMenuBar() {
    QAction *openAboutMenu = new QAction("О программе", this);
    connect(openAboutMenu, SIGNAL(triggered()), this, SLOT(openAboutMenu()));

    QMenu *fileMenu = menuBar()->addMenu("Файл");
    fileMenu->addAction(openAboutMenu);
}

void MainWindow::openAboutMenu() {
    AboutWindow aboutWindow;

    setEnabled(false);
    aboutWindow.exec();
    setEnabled(true);
}

void MainWindow::infoMessage(QString message) {
    statusBar()->showMessage(message);
}
