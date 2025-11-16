#include <QApplication>
#include "TWidget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    TWidget window;
    window.setWindowTitle(QString("Tetris game"));
    window.show();

    return app.exec();
}
