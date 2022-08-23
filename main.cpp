#include "mainwindow.h"

#include <QApplication>
#include <QSplashScreen>
#include <QTimer>

#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile file(":/css/button.css");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());

    a.setStyleSheet(styleSheet);
    a.setWindowIcon(QIcon(":/assets/favicon.ico"));

    MainWindow w;
    w.show();
    return a.exec();
}
