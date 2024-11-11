#pragma once

#include "list.h"


//-------------------------------------------Функции----------------------------------------------------------------------------------------
void check_open         (FILE** f_ptr,const char *name, const char *mode);
list_info *get_list_ptr (void);
void make_list          (list_info *lst, unsigned size);
void designate_free_pos (struct list_info *lst);
