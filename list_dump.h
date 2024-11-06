#pragma once
#ifndef LIST_DUMP_h
#define LIST_DUMP_h
//-------------------------------------------Структуры--------------------------------------------------------------------------

// struct list_info
// {
//     double   *data;
//     unsigned *next;
//     unsigned *prev;
//     unsigned list_size;
//     unsigned head;
//     unsigned tail;
// };

//-------------------------------------------Функции----------------------------------------------------------------------------
// void list_dump (struct list_info *lst, FILE* fp_dump);
// void print_preamble (FILE* fp_dump);
// void print_numbers (const unsigned list_size, FILE* fp_dump);
// void print_list_data (struct list_info *lst, FILE* fp_dump);
// void print_next (struct list_info *lst, FILE* fp_dump);
// void print_prev (struct list_info *lst, FILE* fp_dump);
// void make_arrows (void *array, struct list_info *lst, FILE* fp_dump, const char *symb, const char *type,
//                   const char *array_name, const char *arrow_style, const char *arrow_color,
//                   const char *arrow_fontcolor, const char *null_style, const char *null_color);
// void print_arrows (void *array, struct list_info *lst, unsigned *labels_array, FILE* fp_dump, const char *symb,
//                    const char *type, const char *array_name, const char *arrow_style, const char *arrow_color,
//                    const char *arrow_fontcolor, const char *null_style, const char *null_color);
// void print_null_arrow (void *array,  const char *symb, FILE* fp_dump, const char *array_name, const char *style,
//                        const char *color);
// void do_print_double_arrows (struct list_info *lst, unsigned *labels_array, FILE* fp_dump, const char *symb,
//                              const char *arrow_style, const char *arrow_color, const char *arrow_fontcolor);
// void turn_over_labels_array (unsigned *labels_array, unsigned head, unsigned tail);
// void do_print_unsigned_arrows (unsigned *array, unsigned tail, unsigned head,  unsigned *labels_array,
//                                FILE* fp_dump, const char *symb, const char *arrow_style,const char *arrow_color,
//                                const char *arrow_fontcolor, const char *arrow_null_style);
// unsigned* make_labels_array (struct list_info *lst);
// void fill_labels_array (struct list_info *lst, unsigned *labels_array, unsigned elder_elem_index);
// unsigned find_elder_elem_index (struct list_info *lst);
// void make_alignment (void *array, unsigned head, unsigned tail, FILE* fp_dump, const char *word,
//                      const char *symb, const char *array_name);
// void align_elems (void *array, unsigned head, unsigned tail, FILE* fp_dump, const char *symb,
//                   const char *array_name);
// void do_align_unsigned_elems (unsigned *array, unsigned head, unsigned tail, FILE* fp_dump, const char *symb);
// void do_align_double_elems (double *array, unsigned head, unsigned tail, FILE* fp_dump, const char *symb);
// void align_word (FILE* fp_dump, const char *word);
// void customize_appearance (FILE* fp_dump, const unsigned amount_of_str,...);
// void print_elements (void *array, unsigned head, unsigned tail, FILE* fp_dump, const char *array_name,
//                      const unsigned weight, const char *symb);
// void do_print_double_elements (double* array, unsigned head, unsigned tail, FILE* fp_dump, const char *symb);
// void do_print_unsigned_elements (unsigned *array, unsigned head, unsigned tail, FILE* fp_dump, const char *symb);


//-------------------------------------------Константы--------------------------------------------------------------------------
const unsigned NUMBER_WEIGHT                 = 400;
const unsigned *TEST                         = 0;
// const char     *DATA_NODE_SETTINGS           = "node [shape = \"box3d\", color = green];";
// const char     *DATA_ORDER                   = "\"[0]\"->\"NAN\";";
// const char     *DATA_POISON_COLOR            = "\"NAN\" [color = red];";
// const unsigned AMOUNT_DATA_CUSTOMIZE_STRINGS = 3;
// const char     *NEXT_WORD_SETTINGS           = "\"NEXT:\" [shape=none, fontcolor = \"#03afe8\"];";
// const char     *NEXT_WORD_ORDER              = "\"NAN\"->\"NEXT:\";";
// const char     *NEXT_NODE_SETTINGS           = "node [shape = \"polygon\"];";
// const char     *NEXT_ORDER                   = "\"NEXT:\"->\"->0\";";
// const char     *NEXT_ZERO_COLOR              = "\"->0\"[color = red];";
// const unsigned AMOUNT_NEXT_CUSTOMIZE_STRINGS = 5;
// const char     *PREV_WORD_SETTINGS           = "\"PREV:\"[shape=none, fontcolor = \"#bb2649\"];";
// const char     *PREV_WORD_ORDER              = "\"->0\"->\"PREV:\";";
// const char     *PREV_NODE_SETTINGS           = "node [shape = \"polygon\"];";
// const char     *PREV_ORDER                   = "\"PREV:\"->\"<-0\";";
// const char     *PREV_ZERO_COLOR              = "\"<-0\"[color=red];";
// const unsigned AMOUNT_PREV_CUSTOMIZE_STRING  = 5;
// //const double   DEVIATION                     = 1e-30;
// const unsigned NEXT_WEIGHT                   = 400;
// const unsigned PREV_WEIGHT                   = 400;
// const unsigned DATA_WEIGHT                   = 400;
// const char     *DATA_FIELD                   = ".elem_value";
// const char     *NEXT_FIELD                   = ".next_elem_index";
// const char     *PREV_FIELD                   = ".prev_elem_index";
// const char     *DATA_TYPE                    = "double";
// const char     *NEXT_TYPE                    = "unsigned";
// const char     *PREV_TYPE                    = "unsigned";
// const char     *DATA_SYMB                    = "";
// const char     *NEXT_SYMB                    = "->";
// const char     *PREV_SYMB                    = "<-";
// const char     *NEXT                         = "NEXT:";
// const char     *PREV                         = "PREV:";
// const char     *WITHOUT_WORD                 = "WITHOUT_WORD";
// const char     *ALIGN_BEGINNING              = "{rank = same; ";
// const char     *PREV_ARROW_STYLE             = "style = \"\"";
// const char     *NEXT_ARROW_STYLE             = "style = \"\"";
// const char     *DATA_ARROW_STYLE             = "style = \"\"";
// const char     *PREV_ARROW_COLOR             = "color = red";
// const char     *NEXT_ARROW_COLOR             = "color = blue";
// const char     *DATA_ARROW_COLOR             = "color = white";
// const char     *PREV_ARROW_FONTCOLOR         = "fontcolor = white";
// const char     *NEXT_ARROW_FONTCOLOR         = "fontcolor = white";
// const char     *DATA_ARROW_FONTCOLOR         = "fontcolor = white";
// const char     *OPEN_SQUARE_BRACKET          = "[";
// const char     *CLOSE_SQUARE_BRACKET         = "]";
// const char     *NEXT_NULL_ARROW_STYLE        = "style = \"dashed\"";
// const char     *PREV_NULL_ARROW_STYLE        = "style = \"dashed\"";
// const char     *DATA_NULL_ARROW_STYLE        = "style = \"dashed\"";
// const char     *DATA_ARRAY_NAME              = "data";
// const char     *NEXT_ARRAY_NAME              = "next";
// const char     *PREV_ARRAY_NAME              = "prev";
// const char     *PREV_SPECIFIER               = "%u";
// const char     *NEXT_SPECIFIER               = "%u";
// const char     *DATA_SPECIFIER               = "%lf";
// const unsigned MAX_LABELS_ARRAY_SIZE         = 100;
#endif

