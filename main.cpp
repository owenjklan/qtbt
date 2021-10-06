#include <QApplication>
#include <QPushButton>

#include "qtbt.hpp"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QTBT qtbt;
    qtbt.show();
    return QApplication::exec();
}
