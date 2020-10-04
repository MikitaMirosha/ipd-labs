#include "batterywindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    BatteryWindow window;
    window.setFixedSize(600, 400);
    QFont mainFont("Verdana", 12, QFont::Light, false);
    window.setFont(mainFont);
    window.show();
    return app.exec(); 
}
