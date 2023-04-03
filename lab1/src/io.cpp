#include "io.h"
#include <cstdio>
#include "error_handling.h"

int read_amount(int &n, FILE* f)
{
    int err = 0;
    int a = 0;
    if (fscanf(f, "%d", &a) != 1)
        err = FILE_FORMAT_ERR;
    if (!err)
        n = a;
    if (a <= 0)
        err = FILE_CONTENT_ERR;

    return err;
}