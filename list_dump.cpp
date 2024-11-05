#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#include "list_dump.h"



void list_dump (struct list_info *lst, FILE* fp_dump)
{
    print_preamble (fp_dump);

    print_numbers ((const) lst->list_size, fp_dump);

    #define MODE  1
    print_list_data (lst, fp_dump);
    #undef  MODE

    #define MODE 2
    printf_next (lst, fp_dump);
    #undef  MODE

    #define MODE 3
    print_prev (lst, fp_dump);

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

void print_numbers (const unsigned list_size, FILE* fp_dump)
{
    for (unsigned i = 0; i < list_size-1; i++)
    {
        fprintf (fp_dump,"\"[%u]\"->")
    }

    fprintf (fp_dump,"\"[%u]\"[weight = %u];\n\n\t", list_size-1, NUMBER_WEIGHT);
}

void print_list_data (struct list_info *lst, FILE* fp_dump)
{
    customize_appearance (fp_dump, AMOUNT_DATA_CUSTOMIZE_STRINGS, DATA_NODE_SETTINGS, DATA_ORDER, DATA_POISON_COLOR);

    print_elements (lst, fp_dump, DATA_ARRAY_NAME, DATA_WEIGHT, DATA_SYMB, DATA_TYPE);

    make_alignment (lst, fp_dump, WITHOUT_WORD, DATA_SYMB, DATA_TYPE, DATA_ARRAY_NAME);

    make_arrows    (lst, fp_dump, DATA_SYMB, DATA_TYPE, DATA_ARRAY_NAME);
}

void print_next (struct list_info *lst, FILE* fp_dump)
{
    customize_appearance (fp_dump, AMOUNT_NEXT_CUSTOMIZE_STRINGS, NEXT_WORD_SETTINGS, NEXT_WORD_ORDER,
                          NEXT_NODE_SETTINGS, NEXT_ORDER, NEXT_ZERO_COLOR);

    print_elements (lst, fp_dump, NEXT_ARRAY_NAME, NEXT_WEIGHT, NEXT_SYMB, NEXT_TYPE);

    make_alignment (lst, fp_dump, NEXT, NEXT_SYMB, NEXT_TYPE, NEXT_ARRAY_NAME);

    make_arrows    (lst, fp_dump, NEXT_SYMB, NEXT_TYPE, NEXT_ARRAY_NAME);

}

void print_prev (struct list_info *lst, FILE* fp_dump)
{
    customize_appearance (fp_dump, AMOUNT_PREV_CUSTOMIZE_STRING, PREV_WORD_SETTINGS, PREV_WORD_ORDER, PREV_NODE_SETTINGS,
                          PREV_ORDER, PREV_ZERO_COLOR);

    print_elements (lst, fp_dump, PREV_ARRAY_NAME, PREV_WEIGHT, PREV_SYMB, PREV_TYPE);

    make_alignment (lst, fp_dump, PREV, PREV_SYMB, PREV_TYPE, PREV_ARRAY_NAME);

    make_arrows    (lst, fp_dump, PREV_SYMB, PREV_TYPE, PREV_ARRAY_NAME);
}

void make_arrows (struct list_info *lst, FILE* fp_dump, const char *symb, const char *type,
                  const char *array_name)
{
    unsigned *labels_array = NULL;

    labels_array = make_labels_array (lst);

    print_arrows      (lst, labels_array, fp_dump, symb, type, array_name);
}

void print_arrows (struct list_info *lst, unsigned *labels_array, FILE* fp_dump, const char *symb,
                   const char *type, const char *array_name)
{
    print_null_arrow (lst, symb, fp_dump, array_name );

    if (!strcmp (type, "double"))
        do_print_double_arrows (lst, labels_array, fp_dump, symb, );

    if (!strcmp (type, "unsigned"))
        do_print_unsigned_arrows ();

    else
    {
        printf ("ПРОСЯТ НАРИСОВАТЬ СТРЕЛОЧКИ МЕЖДУ ЭЛЕМЕНТАМИ НЕОЖИДАННОГО ТИПА\n");
        exit (EXIT_FAILURE);
    }
}

void print_null_arrow (struct list_info *lst, const char *symb, FILE* fp_dump, const char *array_name)
{
    #define LST(i) lst->list[i]

    if (!strcmp (array_name, "data"))
    {
        char color[] = DATA_ARROW_COLOR;
        char style[] = DATA_NULL_ARROW_STYLE;
    #if MODE == 1
        #define SPECIFIER "%lf"
        #define FIELD .elem_value
    #endif
    }

    else if (!strcmp (array_name, "next"))
    {
        char color[] = NEXT_ARROW_COLOR;
        char style[] = NEXT_NULL_ARROW_STYLE;

    #if MODE == 2
        #define SPECIFIER "%u"
        #define FIELD .next_elem_index
    #endif
    }

    else if (!strcmp (array_name, "prev"))
    {
        char color[] = PREV_ARROW_COLOR;
        char style[] = PREV_NULL_ARROW_STYLE;

    #if MODE == 3
        #define SPECIFIER "%u"
        #define FIELD .prev_elem_index
    #endif
    }

    else
    {
        printf ("ПРОСЯТ НАРИСОВАТЬ СТРЕЛКУ К НУЛЕВОМУ ЭЛЕМЕНТУ НЕИЗВЕСТНОГО МАССИВА\n");
        exit (EXIT_FAILURE);
    }

    fprintf (fp_dump, "\"%s"SPECIFIER"\"->\"%s"SPECIFIER"\" " "[%s, %s]\n\t", symb, LST(0)FIELD,  symb,
             LST(0)FIELD, style, color);

    #undef FIELD
    #undef LST
    #undef SPECIFIER
}

void do_print_double_arrows (struct list_info *lst, unsigned *labels_array, FILE* fp_dump, const char *symb,
                             const char* array_name, const char *arrow_style, const char *arrow_color,
                             const char *arrow_fontcolor)
{
    #define LST(i) lst->list[i]

    if (!strcmp(array_name, "data"))
        #define FIELD .elem_value

    else
    {
        printf ("ПРОСЯТ НАРИСОВАТЬ СТРЕЛОЧКИ МЕЖДУ ЭЛЕМЕНТАМИ НЕИЗВЕСТНОГО МАССИВА DOUBLE\n");
        exit (EXIT_FAILURE);
    }

    for (unsigned i = lst->tail; i <= lst->head; i++ )
    {
        if (LST(i).next_elem_index != 0)
        {
            fprintf (fp_dump, "\"%s%lf\"->\"%s%lf\" " "[%s, %s, %s, label = \"%u\"]\n\t", symb, LST(i)FIELD, symb,
                     LST(lst->list[i].next_elem_index)FIELD, arrow_style, arrow_color, arrow_fontcolor,
                     labels_array[i]);
        }
        else
            continue
    }

    #undef FIELD
    #undef LST
}

void turn_over_labels_array (unsigned *labels_array, unsigned head, unsigned tail)
{
    for (unsigned i = tail; i <= head; i++)
    {
        labels_array[i] = head-tail+1 - labels_array[i];
    }
}

void do_print_unsigned_arrows (struct list_info *lst, unsigned *labels_array, FILE* fp_dump, const char *symb,
                               const char *array_name, const char *arrow_style, const char *arrow_color,
                               const char *arrow_fontcolor)
{
    #define LST(i) lst->list[i]

    if (!strcmp (array_name, "next"))
    {
        #define FIELD .next_elem_index
    }

    else if (!strcmp (array_name, "prev"))
    {
        #define FIELD .prev_elem_index
        turn_over_labels_array (labels_array, lst->head, lst->tail);
    }

    else
    {
        printf ("ПРОСЯТ СДЕЛАТЬ СТРЕЛКИ МЕЖДУ ЭЛЕМЕНЕТАМИ НЕ ОЖИДАЕМОГО МАССИВА\n");
        exit (EXIT_FAILURE);
    }

    for (unsigned i = lst->tail; i <= lst->head; i++)
    {
        if (LST(LST(i)FIELD)FIELD == 0 && LST(i)FIELD != 0)
        {
            fprintf (fp_dump, "\"%s%u\"->\"%s%NULL\" " "[%s, %s, %s, label = \"%u\"]\n\t", symb, LST(i)FIELD, symb, arrow_style, arrow_color, arrow_fontcolor)
        }

        else if (LST(i)FIELD == 0)
        {
            fprintf (fp_dump, "\"%sNULL\"->\"%s%u\" " "[%s, %s, %s, label = \"%u\"]\n\t", symb, symb,
                     LST(LST(i)FIELD)FIELD, arrow_style, arrow_color, arrow_fontcolor,
                     labels_array[i]);
        }

        else
        {
            fprintf (fp_dump, "\"%s%u\"->\"%s%u\" " "[%s, %s, %s, label = \"%u\"]\n\t", symb,LST(i)FIELD symb,
                     LST(LST(i)FIELD)FIELD, arrow_style, arrow_color, arrow_fontcolor,
                     labels_array[i]);
        }
    }

    #undef FIELD
    #undef LST
}



unsigned* make_labels_array (struct list_info *lst)
{
    static unsigned labels_array[lst->head-lst->tail] = {};
    unsigned elder_elem_index = 0;

    elder_elem_index = find_elder_elem_index (lst);

    if (lst->head - lst->tail >= 0)
        fill_labels_array (lst, labels_array, elder_elem_index);

    else
    {
        printf ("СПИСОК ПУСТ!!!!\n");
        exit (EXIT_FAILURE);
    }

    return labels_array;
}

void fill_labels_array (struct list_info *lst, unsigned *labels_array, unsigned elder_elem_index)
{
    for (unsigned i = lst->head - lst->tail + 1; i != 0; i-- )
    {
        labels_array[elder_elem_index] = i;
        elder_elem_index = lst->list[elder_elem_index].prev_elem_index;
    }
}

unsigned find_elder_elem_index (struct list_info *lst)
{
    unsigned i = lst->tail;
    for (; i < lst->head; i++)
    {
        if (lst->list[i].next_elem_index == 0)
        {
          break;
        }

        else
            continue;
    }

    return i;
}

void make_alignment (struct list_info *lst, FILE* fp_dump, const char *word, const char *symb,
                    const char *type, const char *array_name)
{
    align_word  (lst, fp_dump, word);

    align_elems (lst, fp_dump, symb, type, array_name);

    fprintf (fp_dump, "\n\t");
}

void align_elems (struct list_info *lst, FILE* fp_dump, const char *symb, const char *type,
                  const char *array_name)
{

    if (!strcmp (array_name, "data"))
        do_align_double_elems   (lst, fp_dump, symb, array_name);

    if (!strcmp (array_name, "next") || !strcmp (array_name, "prev"))
        do_align_unsigned_elems (lst, fp_dump, symb, array_name);

    else
    {
        printf ("ПРОСЯТ ВЫРОВНЯТЬ ЭЛЕМЕНТЫ НЕОЖИДАННОГО ТИПА\n");
        exit (EXIT_FAILURE);
    }
}

void do_align_unsigned_elems (struct list_info *lst, FILE* fp_dump, const char *symb, const char *array_name)
{
    #define LST(i) lst->list[i]

    if (!strcmp (array_name, "next"))
    {
        #define FIELD .next_elem_index
    }

    else if (!strcmp (array_name, "prev"))
    {
        #define FIELD .prev_elem_index
    }

    else
    {
        printf ("ПРОСЯТ ВЫРАВНЯТЬ ЭЛЕМЕНЕТЫ НЕИЗВЕСТНОГО МАССИВА\n");
        exit (EXIT_FAILURE);
    }

    for (unsigned i = 0; i <= lst->head; i++)
    {
        if (LST(i)FIELD != 0)
            fprintf (fp_dump, "%s\"%s%lf\"; \"[%u]\"}\n\t", ALIGN_BEGINNING, symb, LST(i)FIELD, i);

        else
            fprintf (fp_dump,"%s\"%sNULL\"; \"[%u]\"}\n\t", ALIGN_BEGINNING, symb, i);
    }

    #undef LST
    #undef FIELD
}

void do_align_double_elems (struct list_info *lst, FILE* fp_dump, const char *symb, const char *array_name)
{
    #define LST(i) lst->list[i]

    if (!strcmp (array_name, data))
    {
        #define FIELD .elem_value
    }

    else
    {
        printf ("ПРОСЯТ ВЫРОВНЯТЬ НЕИЗВЕСТНЫЙ МАССИВ\n");
    }

    for (unsigned i = 0; i <= lst->head; i++)
    {
        fprintf (fp_dump,"%s\"%s%lf\"; \"[%u]\"}\n\t", ALIGN_BEGINNING, symb, LST(i)FIELD, i);
    }
    #undef LST
    #undef FIELD
}

void align_word (struct list_info *lst, FILE* fp_dump, const char *word)
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

void print_elements (struct list_info *lst, FILE* fp_dump, const char *array_name, const unsigned weight,
                     const char *symb, const char *type)
{
    #define LST(i) lst->list[i]

    if (!strcmp (array_name, "next") || !strcmp (array_name, "prev"))
        #define SPECIFIER "%u"


    else if (!strcmp (array_name, "data"))
        #define SPECIFIER "%lf"

    else
    {
        printf ("Тип элементов, которые нужно напечатать не соответствует ожидаемому\n");
        exit (EXIT_FAILURE);
    }

    if (!strcmp (array_name, "data"))
    {
        #define FIELD .elem_value
    }

    else if (!strcmp (array_name, "next"))
    {
        #define FIELD .next_elem_index
    }

    else if (!strcmp (array_name, "prev"))
    {
        #define FIELD .prev_elem_index
    }


    fprintf (fp_dump, "\"%s"SPECIFIER"\"->", symb, LST(0)FIELD);

   if (!strcmp (array_name, "data"))
        do_print_double_elements (lst, fp_dump, symb, array_name);

    if (!strcmp (array_name, "next") || !strcmp (array_name, "prev"))
        do_print_unsigned_elements (lst, fp_dump, symb, array_name);

    if (LST(lst->head)FIELD == 0 && strcmp(type, "data") != 0)
    {
        fprintf (fp_dump,"\"%sNULL\"[weight = %u]\n\n\t",symb, weight);
    }

    else
    {
        fprintf (fp_dump, "\"%s"SPECIFIER"\"[weight = %u]\n\n\t",symb ,LST(lst->head)FIELD ,weight);
    }

    #undef LST
    #undef SPECIFIER
    #undef FIELD
}

void do_print_double_elements (struct list_info *lst, FILE* fp_dump, const char *symb, const char *array_name)
{
    #define LST(i) lst->list[i]

    if (!strcmp (array_name, "data"))
    {
        #define FIELD .elem_value
    }

    else
    {
        printf ("ПРОСЯТ НАПЕЧАТАТЬ ЭЛЕМЕНЕТЫ НЕИЗВЕСТНОГО МАССИВА\n");
        exit (EXIT_FAILURE);
    }


    for (unsigned i = 1; i < lst->head; i++ )
    {
        fprintf (fp_dump, "%s%lf->", symb, LST(i)FIELD);
    }

    #undef LST
    #undef FIELD
}

void do_print_unsigned_elements (struct list_info *lst, FILE* fp_dump, const char *symb, const char *array_name)
{
    #define LST(i) lst->list[i]

    if (!strcmp (array_name, "next"))
    {
        #define FIELD .next_elem_index
    }

    else if (!strcmp (array_name, "prev"))
    {
        #define FIELD .prev_elem_index
    }

    else
    {
        printf ("ПРОСЯТ НАПЕЧАТАТЬ ЭЛЕМЕНЕТЫ НЕИЗВЕСТНОГО МАССИВА\n");
        exit (EXIT_FAILURE);
    }

    for (unsigned i = 1; i < lst->head; i++)
    {
        if (LST(i)FIELD != 0);
        {
            fprintf (fp_dump, "\"%s%u\"->", symb, LST(i)FIELD);
        }

        else
        {
            fprintf (fp_dump, "\"%sNULL\"->", symb);
        }
    }

    #undef LST
    #undef FIELD
}

