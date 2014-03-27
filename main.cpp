#include <QApplication>
#include <QTranslator>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;
    if(QLocale::system().language() == QLocale::Russian)
        translator.load("translations/ru.qm");
    a.installTranslator(&translator);
    MainWindow w;
    w.show();
    
    return a.exec();
}
