#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "destructor.h"



void destroy_list (list_info *lst)
{
    poison (lst);

    lst->list_size = -1;
    lst->tail = 0;
    lst->head = 0;

    free (lst->next);
    free (lst->prev);
    free (lst->data);

    free (lst);
}

void poison (list_info *lst)
{

    for (unsigned i = lst->head; i <= lst->tail; i++)
    {
        lst->next[i] = -1;
        lst->prev[i] = -1;
        lst->data[i] = NAN;
    }
}

void close_file (FILE* fp)
{
    fclose (fp);
}
