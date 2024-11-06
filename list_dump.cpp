// #include <stdio.h>
// #include <math.h>
// #include <string.h>
// #include <stdarg.h>
// #include <stdlib.h>

 #include "list_dump.h"
// #include "constructor.h"
// #include "destructor.h"




// void list_dump (struct list_info *lst, FILE* fp_dump)
// {
//     print_preamble (fp_dump);
//
//     print_numbers ( lst->list_size, fp_dump);
//
//     print_list_data (lst, fp_dump);
//
//     print_next (lst, fp_dump);
//
//     print_prev (lst, fp_dump);
//
// }
//
// void print_preamble (FILE* fp_dump)
// {
//     fprintf (fp_dump, "digraph\n{\n"
//                         "\tbgcolor=\"#000000\";\n"
//                         "\trankdir = LR;\n"
//                         "\tedge [style = \"invis\"];\n"
//                         "\tnode [fontcolor = white, shape = tab, color = \"#818181\"];\n"
//                         "\n\t");
// }
//
// void print_numbers (const unsigned list_size, FILE* fp_dump)
// {
//     for (unsigned i = 0; i < list_size-1; i++)
//     {
//         fprintf (fp_dump,"\"[%u]\"->", i);
//     }
//
//     fprintf (fp_dump,"\"[%u]\"[weight = %u];\n\n\t", list_size-1, NUMBER_WEIGHT);
// }
//
// void print_list_data (struct list_info *lst, FILE* fp_dump)
// {
//     customize_appearance (fp_dump, AMOUNT_DATA_CUSTOMIZE_STRINGS, DATA_NODE_SETTINGS, DATA_ORDER, DATA_POISON_COLOR);
//
//     print_elements (lst->data, lst->head, lst->tail, fp_dump, DATA_ARRAY_NAME, DATA_WEIGHT, DATA_SYMB);
//
//     make_alignment (lst->data, lst->head, lst->tail, fp_dump, WITHOUT_WORD, DATA_SYMB, DATA_ARRAY_NAME);
//
//     make_arrows    (lst->data, lst, fp_dump, DATA_SYMB, DATA_TYPE, DATA_ARRAY_NAME, DATA_ARROW_STYLE,
//                     DATA_ARROW_COLOR, DATA_ARROW_FONTCOLOR, DATA_NULL_ARROW_STYLE, DATA_ARROW_COLOR);
// }
//
// void print_next (struct list_info *lst, FILE* fp_dump)
// {
//     customize_appearance (fp_dump, AMOUNT_NEXT_CUSTOMIZE_STRINGS, NEXT_WORD_SETTINGS, NEXT_WORD_ORDER,
//                           NEXT_NODE_SETTINGS, NEXT_ORDER, NEXT_ZERO_COLOR);
//
//     print_elements (lst->next,lst->head, lst->tail, fp_dump, NEXT_ARRAY_NAME, NEXT_WEIGHT, NEXT_SYMB);
//
//     make_alignment (lst->next, lst->head, lst->tail, fp_dump, NEXT, NEXT_SYMB, NEXT_ARRAY_NAME);
//
//     make_arrows    (lst->next, lst, fp_dump, NEXT_SYMB, NEXT_TYPE, NEXT_ARRAY_NAME, NEXT_ARROW_STYLE,
//                     NEXT_ARROW_COLOR, NEXT_ARROW_FONTCOLOR, NEXT_NULL_ARROW_STYLE, NEXT_ARROW_COLOR);
//
// }
//
// void print_prev (struct list_info *lst, FILE* fp_dump)
// {
//     customize_appearance (fp_dump, AMOUNT_PREV_CUSTOMIZE_STRING, PREV_WORD_SETTINGS, PREV_WORD_ORDER, PREV_NODE_SETTINGS,
//                           PREV_ORDER, PREV_ZERO_COLOR);
//
//     print_elements (lst->prev, lst->head, lst->tail, fp_dump, PREV_ARRAY_NAME, PREV_WEIGHT, PREV_SYMB);
//
//     make_alignment (lst->prev, lst->head, lst->tail, fp_dump, PREV, PREV_SYMB, PREV_ARRAY_NAME);
//
//     make_arrows    (lst->prev, lst, fp_dump, PREV_SYMB, PREV_TYPE, PREV_ARRAY_NAME, PREV_ARROW_STYLE,
//                     PREV_ARROW_COLOR, PREV_ARROW_FONTCOLOR, PREV_NULL_ARROW_STYLE, PREV_ARROW_COLOR);
// }
//
// void make_arrows (void *array, struct list_info *lst, FILE* fp_dump, const char *symb, const char *type,
//                   const char *array_name, const char *arrow_style, const char *arrow_color,
//                   const char *arrow_fontcolor, const char *null_style, const char *null_color)
// {
//     unsigned *labels_array = NULL;
//
//     labels_array = make_labels_array (lst);
//
//     print_arrows      (array, lst, labels_array, fp_dump, symb, type, array_name, arrow_style, arrow_color,
//                        arrow_fontcolor, null_style, null_color);
// }
//
// void print_arrows (void *array, struct list_info *lst, unsigned *labels_array, FILE* fp_dump, const char *symb,
//                    const char *type, const char *array_name, const char *arrow_style, const char *arrow_color,
//                    const char *arrow_fontcolor, const char *null_style, const char *null_color)
// {
//     print_null_arrow (array, symb, fp_dump, array_name, null_style, null_color );
//
//     if (!strcmp (type, "double"))
//         do_print_double_arrows   (lst,  labels_array, fp_dump, symb, arrow_style, arrow_color, arrow_fontcolor);
//
//     if (!strcmp (type, "unsigned"))
//         do_print_unsigned_arrows ((unsigned*)array, lst->head, lst->tail, labels_array, fp_dump, symb,
//                                   arrow_style, arrow_color, arrow_fontcolor,null_style);
//
//     else
//     {
//         printf ("ПРОСЯТ НАРИСОВАТЬ СТРЕЛОЧКИ МЕЖДУ ЭЛЕМЕНТАМИ НЕОЖИДАННОГО ТИПА\n");
//         exit (EXIT_FAILURE);
//     }
// }
//
// void print_null_arrow (void *array,  const char *symb, FILE* fp_dump, const char *array_name, const char *style,
//                        const char *color)
// {
//     if (!strcmp (array_name, "data"))
//     {
//         fprintf (fp_dump, "\"%s%lf\"->\"%s%lf\" " "[%s, %s]\n\t", symb, *((double*)array + 0),  symb,
//                 *((double*)array + 0), style, color);
//     }
//
//     else
//     {
//         fprintf (fp_dump, "\"%s%u\"->\"%s%u\" " "[%s, %s]\n\t", symb, *((unsigned*)array + 0),  symb,
//                 *((unsigned*)array + 0), style, color);
//     }
//
// }
//
// void do_print_double_arrows (struct list_info *lst, unsigned *labels_array, FILE* fp_dump, const char *symb,
//                              const char *arrow_style, const char *arrow_color, const char *arrow_fontcolor)
// {
//     for (unsigned i = lst->tail; i <= lst->head; i++ )
//     {
//         if (lst->next[i] != 0)
//         {
//             fprintf (fp_dump, "\"%s%lf\"->\"%s%lf\" " "[%s, %s, %s, label = \"%u\"]\n\t", symb, lst->data[i], symb,
//                      lst->data[lst->next[i]], arrow_style, arrow_color, arrow_fontcolor,
//                      labels_array[i]);
//         }
//         else
//             continue;
//     }
//
// }
//
// void turn_over_labels_array (unsigned *labels_array, unsigned head, unsigned tail)
// {
//     for (unsigned i = tail; i <= head; i++)
//     {
//         labels_array[i] = head-tail+1 - labels_array[i];
//     }
// }
//
// void do_print_unsigned_arrows (unsigned *array, unsigned tail, unsigned head,  unsigned *labels_array,
//                                FILE* fp_dump, const char *symb, const char *arrow_style,const char *arrow_color,
//                                const char *arrow_fontcolor, const char *arrow_null_style)
// {
//     for (unsigned i = tail; i <= head; i++)
//     {
//         if (array[array[i]] == 0 && array[i] != 0)
//         {
//             fprintf (fp_dump, "\"%s%u\"->\"%sNULL\" " "[%s, %s, %s, label = \"%u\"]\n\t", symb, array[i], symb,
//                      arrow_style, arrow_color, arrow_fontcolor, labels_array[i]);
//         }
//
//         else if (array[i] == 0)
//         {
//             fprintf (fp_dump, "\"%sNULL\"->\"%s%u\" " "[%s, %s, %s, label = \"%u\"]\n\t", symb, symb,
//                      array[array[i]], arrow_null_style, arrow_color, arrow_fontcolor,
//                      labels_array[i]);
//         }
//
//         else
//         {
//             fprintf (fp_dump, "\"%s%u\"->\"%s%u\" " "[%s, %s, %s, label = \"%u\"]\n\t", symb,array[i], symb,
//                      array[array[i]], arrow_style, arrow_color, arrow_fontcolor,
//                      labels_array[i]);
//         }
//     }
//
// }
//
//
//
// unsigned* make_labels_array (struct list_info *lst)
// {
//     static unsigned labels_array[MAX_LABELS_ARRAY_SIZE] = {};
//     unsigned elder_elem_index = 0;
//
//     elder_elem_index = find_elder_elem_index (lst);
//
//     if (lst->head - lst->tail >= 0)
//         fill_labels_array (lst, labels_array, elder_elem_index);
//
//     else
//     {
//         printf ("СПИСОК ПУСТ!!!!\n");
//         exit (EXIT_FAILURE);
//     }
//
//     return labels_array;
// }
//
// void fill_labels_array (struct list_info *lst, unsigned *labels_array, unsigned elder_elem_index)
// {
//     for (unsigned i = lst->head - lst->tail + 1; i != 0; i-- )
//     {
//         labels_array[elder_elem_index] = i;
//         elder_elem_index = lst->prev[i];
//     }
// }
//
// unsigned find_elder_elem_index (struct list_info *lst)
// {
//     unsigned i = lst->tail;
//     for (; i < lst->head; i++)
//     {
//         if (lst->next[i] == 0)
//         {
//           break;
//         }
//
//         else
//             continue;
//     }
//
//     return i;
// }
//
// void make_alignment (void *array, unsigned head, unsigned tail, FILE* fp_dump, const char *word,
//                      const char *symb, const char *array_name)
// {
//     align_word  (fp_dump, word);
//
//     align_elems (array, head, tail, fp_dump, symb, array_name);
//
//     fprintf (fp_dump, "\n\t");
// }
//
// void align_elems (void *array, unsigned head, unsigned tail, FILE* fp_dump, const char *symb,
//                   const char *array_name)
// {
//
//     if (!strcmp (array_name, "data"))
//     {
//         do_align_double_elems   ((double*)array, head, tail, fp_dump, symb);
//     }
//
//     else
//     {
//         do_align_unsigned_elems ((unsigned*)array, head, tail, fp_dump, symb);
//     }
//
// }
//
// void do_align_unsigned_elems (unsigned *array, unsigned head, unsigned tail, FILE* fp_dump, const char *symb)
// {
//
//     for (unsigned i = tail; i <= head; i++)
//     {
//         if (array[i] != 0)
//             fprintf (fp_dump, "%s\"%s%u\"; \"[%u]\"}\n\t", ALIGN_BEGINNING, symb, array[i], i);
//
//         else
//             fprintf (fp_dump,"%s\"%sNULL\"; \"[%u]\"}\n\t", ALIGN_BEGINNING, symb, i);
//     }
// }
//
// void do_align_double_elems (double *array, unsigned head, unsigned tail, FILE* fp_dump, const char *symb)
// {
//     for (unsigned i = tail; i <= head; i++)
//     {
//         fprintf (fp_dump,"%s\"%s%lf\"; \"[%u]\"}\n\t", ALIGN_BEGINNING, symb, array[i], i);
//     }
// }
//
// void align_word (FILE* fp_dump, const char *word)
// {
//     if (!strcmp (word, "WITHOUT_WORD"))
//     {
//         return;
//     }
//
//     else if (!strcmp (word, "NEXT:"))
//     {
//         fprintf (fp_dump, "%s\"%s\"; \"[0]\"}\n\t", ALIGN_BEGINNING, word);
//     }
//
//     else if (!strcmp (word, "PREV:"))
//     {
//         fprintf (fp_dump, "%s\"%s\"; \"[0]\"}\n\t", ALIGN_BEGINNING, word);
//     }
//
//     else
//     {
//         printf ("ПРОСЯТ ВЫРОВНЯТЬ НЕИЗВЕСТНОЕ СЛОВО\n");
//         exit (EXIT_FAILURE);
//     }
//
// }
//
// void customize_appearance (FILE* fp_dump, const unsigned amount_of_str,...)
// {
//     va_list string = {};
//     va_start (string, amount_of_str);
//
//     for (unsigned i = 0; i < amount_of_str; i++)
//     {
//         fprintf (fp_dump, "%s\n\t", va_arg (string, const char*));
//     }
//
//     va_end (string);
// }
//
// void print_elements (void *array, unsigned head, unsigned tail, FILE* fp_dump, const char *array_name,
//                      const unsigned weight, const char *symb)
// {
//
//     if (!strcmp (array_name, "data"))
//     {
//         fprintf (fp_dump, "\"%s%lf\"->", symb, *((double*)array + 0));
//         do_print_double_elements ((double*)array, head, tail, fp_dump, symb);
//     }
//
//     else
//     {
//         fprintf (fp_dump, "\"%s%u\"->", symb, *((unsigned*) array + 0));
//         do_print_unsigned_elements ((unsigned*)array, head, tail, fp_dump, symb);
//     }
//
//     if ((unsigned)array_name[head] == 0 && strcmp(array_name, "data") != 0)
//     {
//         fprintf (fp_dump,"\"%sNULL\"[weight = %u]\n\n\t",symb, weight);
//     }
//
//     else
//     {
//         fprintf (fp_dump, "\"%s%lf\"[weight = %u]\n\n\t",symb ,*((double*)array + head) ,weight);
//     }
//
// }
//
// void do_print_double_elements (double* array, unsigned head, unsigned tail, FILE* fp_dump, const char *symb)
// {
//
//     for (unsigned i = tail; i < head; i++ )
//     {
//         fprintf (fp_dump, "%s%lf->", symb, array[i]);
//     }
//
// }
//
// void do_print_unsigned_elements (unsigned *array, unsigned head, unsigned tail, FILE* fp_dump, const char *symb)
// {
//
//     for (unsigned i = tail; i < head; i++)
//     {
//         if (array[i] != 0)
//         {
//             fprintf (fp_dump, "\"%s%u\"->", symb, array[i]);
//         }
//
//         else
//         {
//             fprintf (fp_dump, "\"%sNULL\"->", symb);
//         }
//     }
//
// }
//
