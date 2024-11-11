#pragma once

//-------------------------------------------Структуры--------------------------------------------------------------------------------------
struct list_info
{
    int      list_size;
    unsigned tail;
    unsigned head;
    double   *data;
    int      *next;
    int      *prev;

};
//-------------------------------------------Функции--------------------------------------------------------------------------------------------------------
void insert_elem_after (struct list_info *lst, double elem, int anchor_position);
void insert_elem_before (struct list_info *lst, double elem, int anchor_position);
void link_elem_to_others_before (struct list_info *lst, int anchor_position, int new_elem_pos);
int find_free_pos (struct list_info *lst);
void link_elem_to_others_after (struct list_info *lst, int anchor_position, int new_elem_pos);
void link_first_elem (struct list_info *lst, int new_elem_pos);
void link_last_elem (struct list_info *lst, int new_elem_pos);
void link_elem_in_empty_list (struct list_info *lst, int new_elem_pos);
void find_out_file_name (char *current_name, unsigned *file_counter, const char* const file_extension);
void delete_elem (struct list_info *lst, int deleted_elem_pos);
void feel_deleted_elem (struct list_info *lst, int deleted_elem_pos);
void make_next_dump_file (FILE **fp_dump, char *current_file_name, unsigned *file_counter );
void find_out_command (char *current_command, char* current_file_name, unsigned file_counter);
void make_bash_script (FILE *fp_bash_script, char *current_command, char* current_file_name, unsigned file_counter);
//-------------------------------------------Константы------------------------------------------------------------------------------------------------------
const int ERROR = -1;
const int OK    = 1;
