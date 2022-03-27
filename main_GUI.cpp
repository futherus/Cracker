#include <unistd.h>
#include <QtWidgets>
#include <QApplication>
#include "mainwindow_GUI.h"

// ----------------------------------------------------------------------
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QCoreApplication::setApplicationName("Cracker");
    app.setFont(QFont("URW Gothic", 18, QFont::Normal));
    MainWindow window(&app);

    QPalette pal;
    pal.setColor(window.foregroundRole(), Qt::white);
    window.setPalette(pal);

    window.show();

    return app.exec();
}
