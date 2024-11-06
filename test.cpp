// #include <stdio.h>
// #include <stdlib.h>
// #include <math.h>
// #include <string.h>
//
//    #include "constructor.h"
// #include "destructor.h"
// #include "list_dump.h"
#include "list_dump.h"


//  void check_open (const char *name, const char *mode);
//  void check_open ( const char *name, const char *mode);

int main (void)
{
const unsigned NUMBER_WEIGHT                 = 400;
const unsigned NUMBER_WEIGHT                 = 400;
//     FILE* fp_dump = NULL;
//
//     check_open (&fp_dump, "test.dot", "w");
//
//     struct list_info lst = {};
//     lst.list_size = 10;
//
//     lst.data = (double*)   calloc (10, sizeof (double));
//     lst.next = (unsigned*) calloc (10, sizeof (unsigned));
//     lst.prev = (unsigned*) calloc (10, sizeof (unsigned));
//
//     lst.head = 6;
//     lst.data[0] = NAN;
//     lst.next[0] = 0;
//     lst.prev[0] = 0;
//
//     for (unsigned i = 1; i <= lst.head; i++ )
//     {
//         lst.data[i] = i*10;
//     }
//
//     for (unsigned i = 1; i <= lst.head -1; i++)
//     {
//         lst.next[i] = i+1;
//     }
//
//     lst.next[lst.head] = 0;
//
//     lst.prev[lst.tail] = 0;
//     for (unsigned i = lst.tail +1; i <= lst.head; i++)
//     {
//         lst.prev[i] = i-1;
//     }
//
//     list_dump (&lst, fp_dump);
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



// void check_open (FILE** f_ptr, const char *name, const char *mode)
// {
//     if ((*f_ptr = fopen(name, mode)) == NULL)
//     {
//         fprintf (stdout, "Не удалось открыть файл\n");
//
//         exit (EXIT_FAILURE);
//     }
//
//     return;
// }
