//types at table.h
#include "table.h"

class DataBase{
private:
	table_vec tables;
	bool interpret_query(str query, str& name, strp_vec& vec, uint_vec& num);
	void add_table(Table* t);
public:
	DataBase();
	void create_table(str query);
};
