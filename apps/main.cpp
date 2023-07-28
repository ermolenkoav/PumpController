#include "../businessLogic/pch.h"
#include "../businessLogic/mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    QApplication::setWindowIcon(QIcon(":/logo.ico"));
    QFont serifFont("Times", 11, 4, false);
    QApplication::setFont(serifFont);
    MainWindow view;
    view.show();
    return app.exec();
}