#include <QApplication>

#include "widgets/mainwindowwidget.h"
#include "model/song.h"

// Entry point of our application
int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    // Create and show our main window. 'mainWindow' is the
    // root QWidget of all QWidgets in this application
    MainWindowWidget mainWindow;
    mainWindow.show();

    // Enters main event loop and waits until exit() is called.
    // No user interaction can take place before this call.
    using namespace as4::model;
    //Melodytrack* track = new Melodytrack;
    //track->play();

    return app.exec();
}
