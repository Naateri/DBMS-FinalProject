#include "db.h"

str create_tab = "CREATE TABLE";

DataBase::DataBase(){
	table_vec tables;
	this->tables = tables;
}

bool DataBase::interpret_query(str query){
	str temp;
	temp = query.substr(0, 10);
	if (temp != create_tab){
		std::cout << "Sintaxis incorrecta.\n";
		return 0;
	}
	return 1;
}

void DataBase::create_table(str query){
	if (!interpret_query(query)) return;
	Table* temp = new Table();
}
