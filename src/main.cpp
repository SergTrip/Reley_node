#include "testjetsondialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TestJetsonDialog w;
    w.show();

    return a.exec();
}
