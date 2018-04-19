#include "types.h"

u_int stringToUint(str a);

void print_vec(strp_vec vec, char_name_vec cvec);

void writeInsert(txt_file& file, str_vec t);

str_vec select_query(read_file& file, str_vec columns); //each position at the vec is a row of data

