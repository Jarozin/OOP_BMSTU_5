//
// Created by jarozin on 25.04.22.
//

#ifndef LAB1_ERROR_HANDLING_H
#define LAB1_ERROR_HANDLING_H
#include <iostream>
#include "QMessageBox"
#include <QObject>

enum errors
{
    NONE,
    FILE_NOT_FOUND,
    FILE_CONTENT_ERR,
    EMPTY_PTR_ERR,
    NO_DOTS,
    FILE_FORMAT_ERR,
    NO_LINKS
};
int error_handling(errors rc);
#endif //LAB1_ERROR_HANDLING_H
