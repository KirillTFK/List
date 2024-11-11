#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "constructor.h"
#include "list.h"

list_info *get_list_ptr (void)
{
    list_info *ptr = NULL;

    ptr = (list_info *) calloc (1, sizeof (list_info ));

    return ptr;
}

void make_list(list_info *lst, unsigned size)
{
    lst->next = (int*)    calloc (size + 1, sizeof (int));

    lst->prev = (int*)    calloc (size + 1, sizeof (int));

    lst->data = (double*) calloc (size + 1 ,sizeof (double));

    lst->list_size = (int)size;


    lst->data[0] = NAN;
    lst->next[0] = 0;
    lst->prev[0] = 0;

    lst->head = 0;
    lst->tail = 0;

    designate_free_pos (lst);
}


void check_open (FILE** f_ptr, const char *name, const char *mode)
{
    if ((*f_ptr = fopen(name, mode)) == NULL)
    {
        fprintf (stdout, "Не удалось открыть файл\n");

        exit (EXIT_FAILURE);
    }

    return;
}

void designate_free_pos (struct list_info *lst)
{
    if (lst == NULL)
    {
        printf ("В %s LST == 0\n", __func__);
        exit (EXIT_FAILURE);
    }

    if (lst->prev == NULL || lst->next == NULL)
    {
        printf ("В %s prev: %p next: %p \n", __func__, lst->prev, lst->next);
        exit (EXIT_FAILURE);
    }

    for (unsigned i = lst->tail + 1; i <= (unsigned)lst->list_size; i++ )
    {
        lst->prev[i] = -1;
        lst->next[i] = -1;
        lst->data[i] = NAN;
    }
}
