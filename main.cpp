#include "dialog.h"
#include "configparser.h"

#include <QApplication>
#include <iostream>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QDir::setCurrent(QCoreApplication::applicationDirPath());
    //ConfigParser parser(":.config");

    Dialog w;

    w.show();

    return a.exec();
}
