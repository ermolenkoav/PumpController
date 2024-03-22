#include <QApplication.h>
#include <QStyleFactory>
#include <QIcon>
#include <QFont>
#include "../businessLogic/mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    QApplication::setWindowIcon(QIcon(":/logo.ico"));
    QFont serifFont("Times", 11, 4, false);
    QApplication::setFont(serifFont);
    MainWindow view(nullptr);
    view.show();
    return QApplication::exec();
}