//
// Created by jarozin on 25.04.22.
//

#ifndef LAB1_ERROR_HANDLING_H
#define LAB1_ERROR_HANDLING_H
#include <iostream>
#include "QMessageBox"
#include <QObject>
#define EMPTY_FILE 1
#define EMPTY_PTR 2
#define FILE_DOESNT_EXIST 3


enum errors
{
    NONE,
    FILE_NOT_FOUND,
    FILE_CONTENT_ERR,
    EMPTY_PTR_ERR,
    NO_DOTS
};
int error_handling(errors rc);
#endif //LAB1_ERROR_HANDLING_H
