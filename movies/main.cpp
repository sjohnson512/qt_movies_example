#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("MyOrg");
    QCoreApplication::setOrganizationDomain("mydemoorg.com");
    QCoreApplication::setApplicationName("Movies");

    MainWindow w;
    w.show();

    return a.exec();
}
