#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "list_dump.h"
#include "list.h"
#include "list_dump.h"
#include "constructor.h"
#include "destructor.h"


int main (void)
{
    FILE* fp_bash_script                            = NULL;
    FILE* fp_dump                                   = NULL;
    unsigned file_counter                           = 1;
    char    current_command[MAX_COMMAND_SIZE]       = "";
    char    current_file_name[MAX_FILE_NAME_SIZE]   = "";

    check_open (&fp_bash_script, SCRIPT_NAME, "w");
    make_next_dump_file (&fp_dump, current_file_name, &file_counter);


    list_info *lst = get_list_ptr ();

    make_list    (lst, 10);

    insert_elem_after (lst, 123.3, 1);
    list_dump (lst, fp_dump);
    make_bash_script (fp_bash_script, current_command, current_file_name, file_counter);
    make_next_dump_file (&fp_dump, current_file_name, &file_counter);

    insert_elem_after (lst, 100.3, 1);
    list_dump (lst, fp_dump);
    make_bash_script (fp_bash_script, current_command, current_file_name, file_counter);
    make_next_dump_file (&fp_dump, current_file_name, &file_counter);

    insert_elem_after (lst, 101.3, 2);
    list_dump (lst, fp_dump);
    make_bash_script (fp_bash_script, current_command, current_file_name, file_counter);
    make_next_dump_file (&fp_dump, current_file_name, &file_counter);

    delete_elem (lst, 2);
    list_dump (lst, fp_dump);
    make_bash_script (fp_bash_script, current_command, current_file_name, file_counter);
    make_next_dump_file (&fp_dump, current_file_name, &file_counter);

    destroy_list (lst);

    close_file (fp_dump);
    close_file (fp_bash_script);
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


void insert_elem_after (struct list_info *lst, double elem, int anchor_position)
{
    int free_pos = 0;

    if(!(free_pos = find_free_pos (lst)))
        return;

    if (lst->head == 0 || lst->tail == 0)
    {
        printf ("СПИСОК ПУСТОЙ, POSITION ИГНОРИРУЕТСЯ\n");

        link_last_elem (lst, free_pos);
    }

    else if ((unsigned)anchor_position == lst->tail)
    {
        link_last_elem (lst, free_pos);
    }

    else if (isnan(lst->data[anchor_position]))
    {
        printf ("ТАКОГО ЭЛЕМЕНТА НЕТ\n");
        return;
    }

    else if (anchor_position == 0)
    {
        printf ("НЕЛЬЗЯ ВСТАВЛЯТЬ ЭЛЕМЕНТЫ ПОСЛЕ НУЛЕВОГО ЭЛЕМЕНТА\n"
                "Hint: ПОПРОБУЙТЕ ВСТАВИТЬ ЭЛЕМЕНТ ДО head'а\n");
        return;
    }

    else
    {
        link_elem_to_others_after (lst, anchor_position, free_pos);
    }

    lst->data[free_pos] = elem;
}

void insert_elem_before (struct list_info *lst, double elem, int anchor_position)
{
    int free_pos = 0;

    if (!(free_pos = find_free_pos (lst)))
        return;

    if (lst->head == 0 || lst->tail == 0)
    {
        printf ("СПИСОК ПУСТОЙ\n");

        link_first_elem (lst, anchor_position);
    }

    else if ((unsigned)anchor_position == lst->head)
    {
        link_first_elem (lst, anchor_position);
    }

    else if (isnan(lst->data[anchor_position]))
    {
        printf ("ТАКОГО ЭЛЕМЕНТА НЕ СУЩЕСТВУЕТ");
        return;
    }

    else if (anchor_position == 0)
    {
        printf ("НЕЛЬЗЯ ВСТАВЛЯТЬ ЭЛЕМЕНТЫ ДО НУЛЕВОГО\n");
        return;
    }

    else
    {
        link_elem_to_others_before (lst, anchor_position, free_pos);
    }

    lst->data[free_pos] = elem;
}

void link_elem_to_others_before (struct list_info *lst, int anchor_position, int new_elem_pos)
{
    lst->next[lst->prev[anchor_position]]   = new_elem_pos;
    lst->prev[new_elem_pos]                 = lst->prev[anchor_position];
    lst->prev[anchor_position]              = new_elem_pos;
    lst->next[new_elem_pos]                 = anchor_position;
}

int find_free_pos (struct list_info *lst)
{
    for (int i = 1; i <= lst->list_size; i++)
    {
        if (lst->next[i] == -1)
            return i;
    }

    printf ("НЕ СМОГ НАЙТИ СВОБОДНУЮ ЯЧЕЙКУ \n");
    return 0;
}

void link_elem_to_others_after (struct list_info *lst, int anchor_position, int new_elem_pos)
{
    lst->next[new_elem_pos]                 = lst->next[anchor_position];
    lst->prev[lst->next[anchor_position]]   = new_elem_pos;
    lst->next[anchor_position]              = new_elem_pos;
    lst->prev[new_elem_pos]                 = anchor_position;

}




void link_first_elem (struct list_info *lst, int new_elem_pos)
{
    if (lst->head != 0)
    {
        lst->prev[lst->head] = new_elem_pos;

        lst->next[new_elem_pos] = (int)lst->head;
        lst->prev[new_elem_pos] = 0;

        lst->head = (unsigned)new_elem_pos;
    }

    else
    {
        link_elem_in_empty_list (lst, new_elem_pos);
    }
}


void link_last_elem (struct list_info *lst, int new_elem_pos)
{
    if (lst->tail != 0)
    {
        lst->next[lst->tail] = new_elem_pos;

        lst->prev[new_elem_pos]  = (int)lst->tail;
        lst->next[new_elem_pos]  = 0;

        lst->tail = (unsigned)new_elem_pos;
    }

    else
    {
        link_elem_in_empty_list (lst, new_elem_pos);
    }
}

void link_elem_in_empty_list (struct list_info *lst, int new_elem_pos)
{
    lst->next[new_elem_pos] = 0;
    lst->prev[new_elem_pos] = 0;

    lst->head = (unsigned)new_elem_pos;
    lst->tail = (unsigned)new_elem_pos;
}

void find_out_file_name (char *current_name, unsigned *file_counter, const char * const file_extension)
{
    char empty_str[MAX_FILE_NAME_SIZE] = "";
    strncpy (current_name, empty_str, MAX_FILE_NAME_SIZE);
    char   file_counter_str[MAX_FILE_COUNTER_STR_SIZE] = "";
    gcvt   ((*file_counter)++, 2, file_counter_str);

    strncpy (current_name, REFERENCE_FILE_NAME, MAX_FILE_NAME_SIZE);
    strncat (current_name, file_counter_str, MAX_FILE_COUNTER_STR_SIZE);
    strncat (current_name, file_extension, MAX_FILE_NAME_SIZE-strlen(REFERENCE_FILE_NAME)-MAX_FILE_COUNTER_STR_SIZE);

}


void delete_elem (struct list_info *lst, int deleted_elem_pos)
{
    if (isnan(lst->data[deleted_elem_pos]))
        printf ("ЭТОГО ЭЛЕМЕНТА НЕ СУЩЕСТВУЕТ\n");

    else
    {
        if (deleted_elem_pos == (int)lst->tail)
        {
            lst->tail = (unsigned)lst->prev[deleted_elem_pos];
            lst->next[lst->prev[deleted_elem_pos]] = lst->next[deleted_elem_pos];

            feel_deleted_elem (lst, deleted_elem_pos);
            return;
        }

        if (deleted_elem_pos == (int)lst->head)
        {
            lst->head = (unsigned)lst->next[deleted_elem_pos];
            lst->prev[lst->next[deleted_elem_pos]] = lst->prev[deleted_elem_pos];

            feel_deleted_elem (lst, deleted_elem_pos);
            return;
        }

        lst->next[lst->prev[deleted_elem_pos]] = lst->next[deleted_elem_pos];
        lst->prev[lst->next[deleted_elem_pos]] = lst->prev[deleted_elem_pos];

        feel_deleted_elem (lst, deleted_elem_pos);


    }
}


void feel_deleted_elem (struct list_info *lst, int deleted_elem_pos)
{
    lst->data[deleted_elem_pos] = NAN;
    lst->next[deleted_elem_pos] = -1;
    lst->prev[deleted_elem_pos] = -1;
}


void make_next_dump_file (FILE **fp_dump, char *current_file_name, unsigned *file_counter )
{
    find_out_file_name (current_file_name, file_counter, FILE_EXTENSION);
    check_open (fp_dump, current_file_name, "w");
}


void make_bash_script (FILE *fp_bash_script, char *current_command, char* current_file_name, unsigned file_counter)
{
    find_out_command (current_command, current_file_name ,file_counter);

    fprintf (fp_bash_script, "%s\n", current_command);
}

void find_out_command (char *current_command, char* current_file_name, unsigned file_counter)
{
    char pick_name[MAX_PICK_SIZE] = {};
    file_counter--;
    find_out_file_name (pick_name, &file_counter, PICK_EXTENSION);

    strncpy (current_command, CALL_DOT, CALL_DOT_SIZE);
    strncat (current_command, current_file_name, MAX_FILE_NAME_SIZE);
    strncat (current_command, " -T png -o ", 13);
    strncat (current_command, pick_name, MAX_PICK_SIZE);
}
