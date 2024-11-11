#pragma once

#include <math.h>

//-------------------------------------------Константы--------------------------------------------------------------------------------------

const double   DATA_POISON = NAN;
const int      NEXT_POISON = -1;
const int      PREV_POISON = -1;
//-------------------------------------------Функции----------------------------------------------------------------------------------------
void destroy_list (list_info *lst);
void poison       (list_info *lst);
void close_file   (FILE* fp_dump);
