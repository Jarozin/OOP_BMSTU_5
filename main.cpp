#include "main_window.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow window;
    Ui::MainWindow mainWindow;
    mainWindow.setupUi(&window);
    window.show();
    //mainWindow.canvas->show();
    return a.exec();
}