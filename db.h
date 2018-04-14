#include "types.h"
#include "table.h"

class DataBase{
private:
	table_vec tables;
	bool interpret_query(str query);
public:
	DataBase();
	void create_table(str query);
};
