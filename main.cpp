#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include "mainwindow.h"




int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow mainWindow;

    mainWindow.show();


    return app.exec();
}


