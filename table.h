#include "structs.h"
//types at structs.h
class Table{
private:
	str name;
	Data* t_data;
public:
	Table(str name, strp_vec& vec, uint_vec nums);
	str getName();
	void desc();
};
