#include "db.h"

str create_tab = "CREATE TABLE ";

DataBase::DataBase(){
	table_vec tables;
	this->tables = tables;
}

bool DataBase::interpret_query(str query, str& name, strp_vec& vec, uint_vec& num){
	str temp, type, type_name;
	int i, int_count, char_count, date_count;
	int_count = char_count = date_count = 0;
	vec.clear();
	temp = query.substr(0, 13); //temp = "CREATE TABLE "
	if (temp != create_tab){
		std::cout << "Sintaxis incorrecta. Vuelva a intentarlo.\n";
		return 0;
	}
	i = 13;
	name.clear();
	while (query[i] != ' '){
		name += query[i];
		i++;
	}
	i++; //so query[i] != ' '
	while (query[i] != ';'){
		type.clear();
		type_name.clear();
		str_pair data_name_pair; //pair of str(type), str(name)
		while (query[i] != ' ' && query[i] != '('){ //filling with type
			type += query[i];
			i++;
		}
		i++;
		if (type == "INTEGER"){
			int_count++; //i++ because next is a space
			while (query[i] != ' ' && query[i] != ';'){ //filling with the name chosen
				type_name += query[i];
				i++;
			}
			data_name_pair.first = type;
			data_name_pair.second = type_name;
			vec.push_back(data_name_pair);
			continue;
		} else if (type == "VARCHAR") {
			char_count++;
		} else if (type == "DATE"){
			date_count++;
		} else {
			std::cout << "Sintaxis incorrecta. Vuelva a intentarlo.\n";
			return 0;
		}
	}
	num.at(0) = (int_count);
	num.at(1) = (char_count);
	num.at(2) = (date_count);
	return 1;
}

void DataBase::add_table(Table* t){
	this->tables.push_back(t);
}

void DataBase::create_table(str query){
	str name;
	strp_vec vec;
	uint_vec num (3);
	if (!interpret_query(query, name, vec, num)) return;
	Table* temp = new Table(name, vec, num);
	add_table(temp);
	std::cout << "Tabla " << temp->getName() << " creada.\n";
	temp->desc();
}
