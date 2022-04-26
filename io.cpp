//
// Created by jarozin on 26.04.22.
//

#include "io.h"
#include <cstdio>
#include "error_handling.h"

int read_amount(int* n, FILE* f)
{
    int err = 0;

    if (fscanf(f, "%d", n) != 1)
        err = FILE_FORMAT_ERR;

    if (*n <= 0)
        err = FILE_CONTENT_ERR;

    return err;
}