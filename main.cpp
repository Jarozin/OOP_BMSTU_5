#include "main_window.h"


int main(int argc, char *argv[])
{
    int err = OK;
    request req;
    req.t = INIT;
    err = task_manager(req);
    QApplication a(argc, argv);
    QMainWindow window;
    Ui::MainWindow mainWindow;
    req.t = LOAD_FILE;
    err = task_manager(req);
    if (!err)
    {
        mainWindow.setupUi(&window);
        window.show();
        return a.exec();
    }
    error_handling((errors)err);
    return OK;
}