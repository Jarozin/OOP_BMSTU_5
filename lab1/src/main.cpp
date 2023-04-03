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
    if (!err) {
        mainWindow.setupUi(&window);
        req.t = DRAW;
        init_draw(req.dr, mainWindow.canvas);
        task_manager(req);
        window.show();
    }
    error_handling((errors)err);
    a.exec();
    return err;
}