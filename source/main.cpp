#include "pch.h"
#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow view;
    //view.setWindowIcon(QIcon(":/logo.ico"));
    view.setWindowTitle("Odorizer");
    view.resize(300, 100);
    view.show();

    return a.exec();
}
