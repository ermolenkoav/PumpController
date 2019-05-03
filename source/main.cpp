#include "pch.h"
#include "common.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
	QApplication::setStyle(QStyleFactory::create("fusion"));
	MainWindow view;
    view.show();
    return a.exec();
}