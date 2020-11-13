#include "mainwindow.h"
#include "chatwindow.h"
#include <QApplication>

// | +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ |
// | =============================================================== |
// | ----------- SimpleSocketChat client by GAMEPLAYER ------------- |
// | =============================================================== |
// | +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ |


int main(int argc, char *argv[])
{
    QCoreApplication::addLibraryPath("./");
    // creating QApplication object
    QApplication a(argc, argv);
    // creating chatwindow object
    chatwindow w;
    // showing chatwindow
    w.show();
    return a.exec();
}
