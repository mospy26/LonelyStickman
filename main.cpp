#include "dialog.h"
#include "configparser.h"

#include <QApplication>
#include <iostream>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QDir::setCurrent(QCoreApplication::applicationDirPath());
    ConfigParser parser(":.config");

    Dialog w(parser[Configuration::BACKGROUND],
                parser[Configuration::SIZE],
                parser[Configuration::MUSIC],
                std::stoi(parser[Configuration::INITIAL_X]),
                std::stoi(parser[Configuration::INITIAL_VELOCITY]),
                nullptr);

    w.show();

    return a.exec();
}
