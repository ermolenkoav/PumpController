#include "../common/pch.h"
#include "../common/common.h"
#include "../common/mainwindow.h"

int main(int argc, char *argv[]) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    QApplication::setStyle(QStyleFactory::create("fusion"));
    QFont serifFont("Times", 11, 4, false);
    QApplication::setFont(serifFont);
    MainWindow view;
    view.show();
    return a.exec();
}