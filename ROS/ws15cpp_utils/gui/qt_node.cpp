#include <QtWidgets/qapplication.h>

#include "ros_qt.h"


int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
    ROSQt window;
    window.show();

    return app.exec();
}