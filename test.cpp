#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "list_dump.h"
#include "list_dump.h"


 void check_open (FILE** f_ptr,const char *name, const char *mode);


int main (void)
{

    FILE* fp_dump = NULL;

    check_open (&fp_dump, "test.dot", "w");

    struct list_info lst = {};
    lst.list_size = 10;

    lst.data = (double*)   calloc (10, sizeof (double));
    lst.next = (unsigned*) calloc (10, sizeof (unsigned));
    lst.prev = (unsigned*) calloc (10, sizeof (unsigned));

    lst.head = 6;
    lst.data[0] = NAN;
    lst.next[0] = 0;
    lst.prev[0] = 0;
    lst.tail = 1;

    for (unsigned i = lst.tail; i <= lst.head; i++ )
    {
        lst.data[i] = i*10;
    }

    lst.data[6] = 25;


    lst.next[1] = 2;
    lst.next[2] = 6;
    lst.next[4] = 5;
    lst.next[5] = 0;
    lst.next[6] = 3;
    lst.next[3] = 4;

    lst.prev[1] = 0;
    lst.prev[2] = 1;
    lst.prev[3] = 6;
    lst.prev[4] = 3;
    lst.prev[5] = 4;
    lst.prev[6] = 2;

    list_dump (&lst, fp_dump);
}

// int main (void)
// {
//     char specifier[] = "%lf";
//     double array [1] = {1};
//     char type[] = "double";
//
//     if (!strcmp (type, "double"))
//     {
//         typedef double type_t;
//     }
//
//     if (!strcmp (type, "unsigned"))
//         typedef unsigned type_t;
//
//     printf("        Stack capacity: " DATA_COL "%zu\n" RESET_COL, 8);
// }



void check_open (FILE** f_ptr, const char *name, const char *mode)
{
    if ((*f_ptr = fopen(name, mode)) == NULL)
    {
        fprintf (stdout, "Не удалось открыть файл\n");

        exit (EXIT_FAILURE);
    }

    return;
}
