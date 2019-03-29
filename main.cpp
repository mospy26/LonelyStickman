#include "dialog.h"
#include "newconfiguration.h"

#include <QApplication>
#include <iostream>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QDir::setCurrent(QCoreApplication::applicationDirPath());

    NewConfiguration n;
    n.show();

    return a.exec();
}
