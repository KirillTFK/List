#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

#include "list_dump.h"

void list_dump (struct list_info *lst, FILE* fp_dump)
{
    print_preamble (fp_dump);

    print_numbers ( lst->list_size, fp_dump);

    print_list_data (lst, fp_dump);

    print_next (lst, fp_dump);

    print_prev (lst, fp_dump);

    print_closing_bracket (fp_dump);
}

void print_preamble (FILE* fp_dump)
{
    fprintf (fp_dump, "digraph\n{\n"
                        "\tbgcolor=\"#000000\";\n"
                        "\trankdir = LR;\n"
                        "\tedge [style = \"invis\"];\n"
                        "\tnode [fontcolor = white, shape = tab, color = \"#818181\"];\n"
                        "\n\t");
}

void print_numbers (const int list_size, FILE* fp_dump)
{
    for (int i = 0; i <= list_size; i++)
    {
        fprintf (fp_dump,"\"[%d]\"->", i);
    }

    fprintf (fp_dump,"\"[%d]\"[weight = %u];\n\n\t", list_size-1, NUMBER_WEIGHT);
}

void print_list_data (struct list_info *lst, FILE* fp_dump)
{
    customize_appearance (fp_dump, AMOUNT_DATA_CUSTOMIZE_STRINGS, DATA_NODE_SETTINGS, DATA_ORDER, DATA_POISON_COLOR);

    print_elements (lst->data, (unsigned)lst->list_size, fp_dump, DATA_ARRAY_NAME, DATA_WEIGHT, DATA_SYMB);

    make_alignment (lst->data, (unsigned)lst->list_size, fp_dump, WITHOUT_WORD, DATA_SYMB, DATA_ARRAY_NAME);

    make_arrows    (lst->data, lst, fp_dump, DATA_SYMB, DATA_TYPE, DATA_ARRAY_NAME, DATA_ARROW_STYLE,
                    DATA_ARROW_COLOR, DATA_ARROW_FONTCOLOR, DATA_NULL_ARROW_STYLE, DATA_ARROW_COLOR);
}

void print_next (struct list_info *lst, FILE* fp_dump)
{
    customize_appearance (fp_dump, AMOUNT_NEXT_CUSTOMIZE_STRINGS, NEXT_WORD_SETTINGS, NEXT_WORD_ORDER,
                          NEXT_NODE_SETTINGS, NEXT_ORDER, NEXT_ZERO_COLOR);

    print_elements (lst->next, (unsigned)lst->list_size, fp_dump, NEXT_ARRAY_NAME, NEXT_WEIGHT, NEXT_SYMB);

    make_alignment (lst->next, (unsigned)lst->list_size, fp_dump, NEXT, NEXT_SYMB, NEXT_ARRAY_NAME);

    make_arrows    (lst->next, lst, fp_dump, NEXT_SYMB, NEXT_TYPE, NEXT_ARRAY_NAME, NEXT_ARROW_STYLE,
                    NEXT_ARROW_COLOR, NEXT_ARROW_FONTCOLOR, NEXT_NULL_ARROW_STYLE, NEXT_ARROW_COLOR);

}

void print_prev (struct list_info *lst, FILE* fp_dump)
{
    customize_appearance (fp_dump, AMOUNT_PREV_CUSTOMIZE_STRING, PREV_WORD_SETTINGS, PREV_WORD_ORDER, PREV_NODE_SETTINGS,
                          PREV_ORDER, PREV_ZERO_COLOR);

    print_elements (lst->prev, (unsigned)lst->list_size, fp_dump, PREV_ARRAY_NAME, PREV_WEIGHT, PREV_SYMB);

    make_alignment (lst->prev, (unsigned)lst->list_size, fp_dump, PREV, PREV_SYMB, PREV_ARRAY_NAME);

    make_arrows    (lst->prev, lst, fp_dump, PREV_SYMB, PREV_TYPE, PREV_ARRAY_NAME, PREV_ARROW_STYLE,
                    PREV_ARROW_COLOR, PREV_ARROW_FONTCOLOR, PREV_NULL_ARROW_STYLE, PREV_ARROW_COLOR);
}

void make_arrows (void *array, struct list_info *lst, FILE* fp_dump, const char *symb, const char *type,
                  const char *array_name, const char *arrow_style, const char *arrow_color,
                  const char *arrow_fontcolor, const char *null_style, const char *null_color)
{
    unsigned *labels_array = NULL;

    labels_array = make_labels_array (lst, array_name);

    print_arrows      (array, lst, labels_array, fp_dump, symb, type, array_name, arrow_style, arrow_color,
                       arrow_fontcolor, null_style, null_color);
}

void print_arrows (void *array, struct list_info *lst, unsigned *labels_array, FILE* fp_dump, const char *symb,
                   const char *type, const char *array_name, const char *arrow_style, const char *arrow_color,
                   const char *arrow_fontcolor, const char *null_style, const char *null_color)
{
    print_null_arrow (array, symb, fp_dump, array_name, null_style, null_color );

    if (!strcmp (type, "double"))
        do_print_double_arrows   (lst,  labels_array, fp_dump, symb, arrow_style, arrow_color, arrow_fontcolor);

    else if (!strcmp (type, "int"))
    {
        do_print_int_arrows ((int*)array, (unsigned)lst->list_size, labels_array, fp_dump, symb,
                                  arrow_style, arrow_color, arrow_fontcolor,null_style);
    }

    else
    {
        printf ("ПРОСЯТ НАРИСОВАТЬ СТРЕЛОЧКИ МЕЖДУ ЭЛЕМЕНТАМИ НЕОЖИДАННОГО ТИПА\n");
        exit (EXIT_FAILURE);
    }
}

void print_null_arrow (void *array,  const char *symb, FILE* fp_dump, const char *array_name, const char *style,
                       const char *color)
{
    if (!strcmp (array_name, "data"))
    {
        fprintf (fp_dump, "\"%s%lf\"->\"%s%lf\" " "[%s, %s]\n\t", symb, *((double*)array + 0),  symb,
                *((double*)array + 0), style, color);
    }

    else
    {
        fprintf (fp_dump, "\"%s%d\"->\"%s%d\" " "[%s, %s]\n\t", symb, *((int*)array + 0),  symb,
                *((int*)array + 0), style, color);
    }

}

void do_print_double_arrows (struct list_info *lst, unsigned *labels_array, FILE* fp_dump, const char *symb,
                             const char *arrow_style, const char *arrow_color, const char *arrow_fontcolor)
{
    for (unsigned i = 1; i <= (unsigned)lst->list_size; i++ )
    {
        if (lst->next[i] != 0 && lst->next[i] != -1)
        {
            fprintf (fp_dump, "\"%s%lf\n[%u]\"->\"%s%lf\n[%d]\" " "[%s, %s, %s, label = \"%u\"]\n\t", symb, lst->data[i], i, symb,
                     lst->data[lst->next[i]], lst->next[i], arrow_style, arrow_color, arrow_fontcolor,
                     labels_array[i]);
        }
        else
            continue;
    }

    fprintf (fp_dump, "\n\t");
}

void turn_over_labels_array (unsigned *labels_array, unsigned list_size, unsigned num_of_elements)
{
    for (unsigned i = 1; i <= list_size; i++)
    {
        if (labels_array[i] == 0)
            continue;

        else
        {
            labels_array[i] = num_of_elements - labels_array[i] +1;
        }
    }
}

void do_print_int_arrows (int *array, unsigned list_size,  unsigned *labels_array,
                               FILE* fp_dump, const char *symb, const char *arrow_style,const char *arrow_color,
                               const char *arrow_fontcolor, const char *arrow_null_style)
{
    for (unsigned i = 1; i <= list_size; i++)
    {
        if (array[array[i]] == 0 && array[i] != 0 && array[i] != -1)
        {
            fprintf (fp_dump, "\"%s%d\n[%u]\"->\"%sNULL\n[%d]\" " "[%s, %s, %s, label = \"%u\"]\n\t", symb, array[i], i, symb, array[i],
                     arrow_style, arrow_color, arrow_fontcolor, labels_array[i]);
        }

        else if (array[i] == 0 )
        {
            fprintf (fp_dump, "\"%sNULL\n[%u]\"->\"%s%d\" " "[%s, %s, %s, label = \"%u\"]\n\t", symb, i, symb,
                     array[array[i]], arrow_null_style, arrow_color, arrow_fontcolor,
                     labels_array[i]);
        }

        else if (array[i] != -1)
        {
            fprintf (fp_dump, "\"%s%d\n[%u]\"->\"%s%d\n[%d]\" " "[%s, %s, %s, label = \"%u\"]\n\t", symb, array[i], i, symb,
                     array[array[i]], array[i], arrow_style, arrow_color, arrow_fontcolor,
                     labels_array[i]);
        }
    }
    fprintf (fp_dump, "\n\t");
}



unsigned *make_labels_array (struct list_info *lst, const char *array_name)
{
    static unsigned labels_array[MAX_LABELS_ARRAY_SIZE] = {};
    int elder_elem_index = 0;

    elder_elem_index = find_elder_elem_index (lst);
    unsigned num_of_elements = find_out_num_of_elements (lst->data, (unsigned)lst->list_size);

    if (lst->tail - lst->head >= 0)
    {
        fill_labels_array (lst, labels_array, elder_elem_index, num_of_elements);
    }

    else
    {
        printf ("СПИСОК ПУСТ!!!!\n");
        exit (EXIT_FAILURE);
    }

    if (!strcmp (array_name, "prev"))
    {
        turn_over_labels_array (labels_array, (unsigned)lst->list_size, num_of_elements);
    }

    return labels_array;
}

void fill_labels_array (struct list_info *lst, unsigned *labels_array, int elder_elem_index, unsigned num_of_elements)
{
    for (unsigned i = num_of_elements; i != 0; i-- )
    {
        labels_array[elder_elem_index] = i;
        elder_elem_index = lst->prev[elder_elem_index];
    }
}


unsigned find_out_num_of_elements (double *data, unsigned list_size)
{
    unsigned num_of_elements = 0;
    for (unsigned i = 1; i <= list_size; i++)
    {
        if (!isnan(data[i]))
        {
            num_of_elements++;
        }
    }

    return num_of_elements;
}

int find_elder_elem_index (struct list_info *lst)
{
    int i = 1;
    for (; i <= lst->list_size; i++)
    {
        if (lst->next[i] == 0)
        {
          break;
        }

        else
            continue;
    }
    return i;
}

void make_alignment (void *array, unsigned list_size, FILE* fp_dump, const char *word, const char *symb, const char *array_name)
{
    align_word  (fp_dump, word);

    align_elems (array, list_size, fp_dump, symb, array_name);

    fprintf (fp_dump, "\n\t");
}

void align_elems (void *array, unsigned list_size, FILE* fp_dump, const char *symb, const char *array_name)
{

    if (!strcmp (array_name, "data"))
    {
        do_align_double_zero_elem (*((double*)array), fp_dump, symb);
        do_align_double_elems     ((double*)array, list_size, fp_dump, symb);
    }

    else
    {
        do_align_int_zero_elem (*((int*)array), fp_dump, symb);
        do_align_int_elems     ((int*)array, list_size, fp_dump, symb);
    }

}

void do_align_double_zero_elem (double zero_elem, FILE* fp_dump, const char *symb)
{
    fprintf (fp_dump, "%s\"%s%lf\"; \"[0]\"}\n\t", ALIGN_BEGINNING, symb, zero_elem);
}



void do_align_int_elems (int *array, unsigned list_size, FILE* fp_dump, const char *symb)
{

    for (unsigned i = 1; i <= list_size; i++)
    {
        if (array[i] != 0)
            fprintf (fp_dump, "%s\"%s%d\n[%u]\"; \"[%u]\"}\n\t", ALIGN_BEGINNING, symb, array[i], i, i);

        else
            fprintf (fp_dump,"%s\"%sNULL\n[%u]\"; \"[%u]\"}\n\t", ALIGN_BEGINNING, symb, i, i);
    }
}

void do_align_int_zero_elem (int zero_elem, FILE* fp_dump, const char *symb)
{
    fprintf (fp_dump, "%s\"%s%d\"; \"[0]\"}\n\t", ALIGN_BEGINNING, symb, zero_elem);
}

void do_align_double_elems (double *array, unsigned list_size, FILE* fp_dump, const char *symb)
{
    for (unsigned i = 1; i <= list_size; i++)
    {
        fprintf (fp_dump,"%s\"%s%lf\n[%u]\"; \"[%u]\"}\n\t", ALIGN_BEGINNING, symb, array[i], i, i);
    }
}

void align_word (FILE* fp_dump, const char *word)
{
    if (!strcmp (word, "WITHOUT_WORD"))
    {
        return;
    }

    else if (!strcmp (word, "NEXT:"))
    {
        fprintf (fp_dump, "%s\"%s\"; \"[0]\"}\n\t", ALIGN_BEGINNING, word);
    }

    else if (!strcmp (word, "PREV:"))
    {
        fprintf (fp_dump, "%s\"%s\"; \"[0]\"}\n\t", ALIGN_BEGINNING, word);
    }

    else
    {
        printf ("ПРОСЯТ ВЫРОВНЯТЬ НЕИЗВЕСТНОЕ СЛОВО\n");
        exit (EXIT_FAILURE);
    }

}

void customize_appearance (FILE* fp_dump, const unsigned amount_of_str,...)
{
    va_list string = {};
    va_start (string, amount_of_str);

    for (unsigned i = 0; i < amount_of_str; i++)
    {
        fprintf (fp_dump, "%s\n\t", va_arg (string, const char*));
    }

    va_end (string);
}

void print_elements (void *array, unsigned list_size, FILE* fp_dump, const char *array_name, const unsigned weight, const char *symb)
{

    if (!strcmp (array_name, "data"))
    {
        fprintf (fp_dump, "\"%s%lf\"->", symb, *((double*)array + 0));
        do_print_double_elements ((double*)array, list_size, fp_dump, symb);
    }

    else
    {
        fprintf (fp_dump, "\"%s%d\"->", symb, *((int*) array + 0));
        do_print_int_elements ((int*)array, list_size, fp_dump, symb);
    }

    if (*((int*)array + list_size) == 0 && strcmp(array_name, "data") != 0)
    {
        fprintf (fp_dump,"\"%sNULL\n[%u]\"[weight = %u]\n\n\t",symb, list_size, weight);
    }

    else if (!strcmp (array_name, "data"))
    {
        fprintf (fp_dump, "\"%s%lf\n[%u]\"[weight = %u]\n\n\t",symb ,*((double*)array + list_size), list_size, weight);
    }

    else
    {
        fprintf (fp_dump, "\"%s%d\n[%u]\"[weight = %u]\n\n\t", symb, *((int*)array + list_size), list_size, weight);
    }

}

void do_print_double_elements (double* array, unsigned list_size, FILE* fp_dump, const char *symb)
{

    for (unsigned i = 1; i <= list_size; i++ )
    {
        fprintf (fp_dump, "\"%s%lf\n[%u]\"->", symb, array[i], i);
    }

}

void do_print_int_elements (int *array, unsigned list_size, FILE* fp_dump, const char *symb)
{

    for (unsigned i = 1; i <= list_size; i++)
    {
        if (array[i] != 0)
        {
            fprintf (fp_dump, "\"%s%d\n[%u]\"->", symb, array[i], i);
        }

        else
        {
            fprintf (fp_dump, "\"%sNULL\n[%u]\"->", symb, i);
        }
    }

}

void print_closing_bracket (FILE* fp_dump)
{
    fprintf (fp_dump, "}\n");
}
