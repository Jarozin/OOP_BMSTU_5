//
// Created by jarozin on 25.04.22.
//

#include "error_handling.h"
int error_handling(errors rc)
{
    switch (rc)
    {
        case NONE:
            break;
        case FILE_NOT_FOUND:
            QMessageBox::critical(NULL, "ERROR", "File is broken, or doesn't exist");
        case FILE_CONTENT_ERR:
            QMessageBox::critical(NULL, "ERROR", "File has wrong content");
            break;
        case EMPTY_PTR_ERR:
            QMessageBox::critical(NULL, "ERROR", "Error with memory allocation");
            break;
        case NO_DOTS:
            QMessageBox::critical(NULL, "ERROR", "File is empty, or array is empty!");
            break;
        case FILE_FORMAT_ERR:
            QMessageBox::critical(NULL, "ERROR", "File format error");
            break;
        case NO_LINKS:
            QMessageBox::critical(NULL, "ERROR", "cube has no links");
            break;
    }
    return rc;
}