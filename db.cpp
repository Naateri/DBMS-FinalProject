#include "db.h"

str create_tab = "CREATE TABLE ";
str insert_into = "INSERT INTO ";
str select = "SELECT ";
str where = "WHERE ";
str del = "DELETE FROM ";
str upd = "UPDATE FROM ";

txt_file tables_txt;
read_file tables_txt2;

char comparisons[3] = {'<', '>', '='};

DataBase::DataBase(){
	table_vec tables;
	this->tables = tables;
}

bool DataBase::interpret_query(str query, str& name, strp_vec& vec, char_name_vec& cvec, uint_vec& num){
	str temp, type, type_name, char_num;
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
	while (query[i] != ';' && query[i] != ' '){
		type.clear();
		type_name.clear();
		str_pair data_name_pair; //pair of str(type), str(name)
		char_name char_name_pair;
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
			i++;
		} else if (type == "VARCHAR") {
			char_count++;
			char_num.clear();
			while (query[i] != ')' && query[i] != ';'){ //filling with the amount of bytes chosen
				char_num += query[i];
				i++;
			}
			i++; //i is now ' ' 
			i++; //i is now the letter
			while (query[i] != ' ' && query[i] != ';'){
				type_name += query[i];
				i++;
			}
			
			data_name_pair.first = type;
			data_name_pair.second = type_name;
			
			char_name_pair.first = type_name;
			char_name_pair.second = stringToUint(char_num); //n chars
			
			vec.push_back(data_name_pair);
			cvec.push_back(char_name_pair);
			
			i++;
		} else if (type == "DATE"){
			date_count++;
			while (query[i] != ' ' && query[i] != ';'){ //filling with the name chosen
				type_name += query[i];
				i++;
			}
			data_name_pair.first = type;
			data_name_pair.second = type_name;
			vec.push_back(data_name_pair);
			
			i++;
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

bool DataBase::interpret_query_i(str query, str& name, str_vec& values){
	str temp, temp2;
	int i;
	values.clear();
	temp = query.substr(0, 12); //temp = "INSERT INTO "
	if (temp != insert_into){
		std::cout << "Sintaxis incorrecta. Vuelva a intentarlo.\n";
		return 0;
	}
	i = 12;
	name.clear();
	while (query[i] != ' '){ //getting the name of the table
		name += query[i];
		i++;
	}
	i++; //so query[i] != ' '
	for (int j = 0; j < 7; j++){
		temp2 += query[i++];
	}
	if (temp2 != "VALUES "){
		std::cout << "Sintaxis incorrecta. Vuelva a intentarlo.\n";
		return 0;
	}
	while (query[i] != ';' && query[i] != ' '){
		temp.clear();
		while (query[i] != ' ' && query[i] != ';'){ //filling with type
			temp += query[i];
			i++;
		}
		i++;
		values.push_back(temp);
	}
	return 1;
}

bool DataBase::interpret_query_s(str query, str& name, str_vec& values, str& column){
	str temp, temp2;
	int i;
	values.clear();
	temp = query.substr(0, 7); //temp = "SELECT "
	if (temp != select){
		std::cout << "Sintaxis incorrecta. Vuelva a intentarlo.\n";
		return 0;
	}
	i = 7;
	while (query[i] != ',' && query[i] != ' '){ //getting the data to fill
		if (query[i] == '*'){
			i++; //i = ' '
			temp = "*";
			values.push_back(temp);
			break;
		}
		temp.clear();
		while (query[i] != ' ' && query[i] != ';'){ //filling with type
			temp += query[i];
			i++;
		}
		i++;
		values.push_back(temp);
	}
	i++; //query[i] is NOT ' ' now
	for (int j = 0; j < 5; j++){
		temp2 += query[i++];
	}
	if (temp2 != "FROM "){
		std::cout << "Sintaxis incorrecta. Vuelva a intentarlo.\n";
		return 0;
	}
	name.clear();
	while (query[i] != ' '){ //getting the name of the table
		name += query[i];
		i++;
	}
	i++;
	if (query[i] == ';') return 1;
	//WHERE clause
	temp.clear();
	for(int j = 0; j < 6; j++){
		temp += query[i++];
	}
	if (temp != "WHERE "){
		std::cout << "Sintaxis incorrecta. Vuelva a intentarlo.\n";
		return 0;
	}
	this->query_where = 1; //WHERE SYNTAX ENABLED
	this->values_to_compare.clear(); //where the values to compare will be added
	char comp;
	column.clear();
	while (query[i] != ' '){
		column += query[i++]; //column name is being stored
	}
	i++; //i should now be the comparator
	comp = query[i++]; //comp is the comparator, and i is a space
	this->comparator = findInArray(comp, comparisons, 3);
	//if comp is not in comparisons std::cout << "Comparador no permitido.\n";
	i++;
	temp.clear(); //this should be inside another loop
	//Will be fixed when I have to do boolean operators
	while (query[i] != ' '){ //getting the value of the atribute
		temp += query[i];
		i++;
	}
	this->values_to_compare.push_back(temp);
	return 1;
}

bool DataBase::interpret_query_d(str query, str& name, str_vec& values, str& column){
	str temp, temp2;
	int i;
	values.clear();
	temp = query.substr(0, 12); //temp = "DELETE FROM "
	if (temp != del){
		std::cout << "Sintaxis incorrecta. Vuelva a intentarlo.\n";
		return 0;
	}
	i = 12;
	name.clear();
	while (query[i] != ' '){ //getting the name of the table
		name += query[i];
		i++;
	}
	i++; //so query[i] != ' '
	//WHERE clause
	temp.clear();
	for(int j = 0; j < 6; j++){
		temp += query[i++];
	}
	if (temp != "WHERE "){
		std::cout << "Sintaxis incorrecta. Vuelva a intentarlo.\n";
		return 0;
	}
	this->query_where = 1; //WHERE SYNTAX ENABLED
	this->values_to_compare.clear(); //where the values to compare will be added
	char comp;
	column.clear();
	while (query[i] != ' '){
		column += query[i++]; //column name is being stored
	}
	i++; //i should now be the comparator
	comp = query[i++]; //comp is the comparator, and i is a space
	this->comparator = findInArray(comp, comparisons, 3);
	//if comp is not in comparisons std::cout << "Comparador no permitido.\n";
	i++;
	temp.clear(); //this should be inside another loop
	//Will be fixed when I have to do boolean operators
	while (query[i] != ' '){ //getting the value of the atribute
		temp += query[i];
		i++;
	}
	this->values_to_compare.push_back(temp);
	return 1;
}

bool DataBase::interpret_query_u(str query, str& name, str_vec& values, str& column, str_vec& columns){
	str temp, temp2;
	int i;
	values.clear();
	temp = query.substr(0, 12); //temp = "UPDATE FROM "
	if (temp != upd){
		std::cout << "Sintaxis incorrecta. Vuelva a intentarlo.\n";
		return 0;
	}
	i = 12;
	name.clear();
	while (query[i] != ' '){ //getting the name of the table
		name += query[i];
		i++;
	}
	i++; //so query[i] != ' '
	for (int j = 0; j < 4; j++){
		temp2 += query[i++];
	}
	if (temp2 != "SET "){
		std::cout << "Sintaxis incorrecta. Vuelva a intentarlo.\n";
		return 0;
	}
	while ( /*query[i] != 'W' && */query[i] != ' '){
		temp.clear();
		if (query[i] == 'W'){
			temp2.clear();
			for (int j = 0; j < 6; j++){
				temp2 += query[i+j];
			}
			if (temp2 == "WHERE ") break;
		}
		temp2.clear();
		while (query[i] != ' ' && query[i] != ';'){ //filling with type
			temp += query[i];
			i++;
		}
		i++;
		columns.push_back(temp);
		if (query[i] != '=') {
			std::cout << "Sintaxis incorrecta. Vuelva a intentarlo.\n";
			return 0;
		}
		i++;
		i++; //i is not empty now
		temp2.clear();
		while (query[i] != ' '){ //value
			temp2 += query[i++];
		}
		values.push_back(temp2);
		i++; //space omitted
	}
	i += 6; //ommitting "WHERE "
	this->query_where = 1; //WHERE SYNTAX ENABLED
	this->values_to_compare.clear(); //where the values to compare will be added
	char comp;
	column.clear();
	while (query[i] != ' '){
		column += query[i++]; //column name is being stored
	}
	i++; //i should now be the comparator
	comp = query[i++]; //comp is the comparator, and i is a space
	this->comparator = findInArray(comp, comparisons, 3);
	//if comp is not in comparisons std::cout << "Comparador no permitido.\n";
	i++;
	temp.clear(); //this should be inside another loop
	//Will be fixed when I have to do boolean operators
	while (query[i] != ' '){ //getting the value of the atribute
		temp += query[i];
		i++;
	}
	this->values_to_compare.push_back(temp);
	return 1;
}

void DataBase::add_table(Table* t){
	this->tables.push_back(t);
}

void DataBase::create_table(str query){
	str name;
	strp_vec vec;
	char_name_vec cvec;
	uint_vec num (3);
	int i;
	
	if (!interpret_query(query, name, vec, cvec, num)) return;
	Table* temp = new Table(name, vec, num, cvec);
	add_table(temp);
	
	tables_txt.open("tables.rlpa", std::fstream::app); //adding to the file in hdd
	writeTable(tables_txt, temp);
	tables_txt.close();
	
	name += ".table";
	char* file_name = new char[name.size() + 1];
	for (i = 0; i < name.size(); i++){
		file_name[i] = name.at(i);
	}
	file_name[i] = '\0';
	tables_txt.open(file_name);
	writeHeaderTable(tables_txt, temp);
	tables_txt.close();
	
	delete [] file_name;
	
	std::cout << "Tabla " << temp->getName() << " creada.\n";
	temp->desc();
}

void DataBase::insert_row(str query){
	str name;
	str_vec vec;
	int i;
	
	if (!interpret_query_i(query, name, vec)) return;
	name += ".table";
	char* file_name = new char[name.size() + 1];
	for (i = 0; i < name.size(); i++){
		file_name[i] = name.at(i);
	}
	file_name[i] = '\0';
	tables_txt.open(file_name, std::fstream::app);
	//write the info retrieved to file_name
	writeInsert(tables_txt, vec);
	tables_txt.close();
	
	delete [] file_name;
	std::cout << "Datos insertados.\n";
	
}

void DataBase::select_data(str query){
	str name, result, column, temp_name;
	str_vec vec;
	int i;
	result.clear();
	
	if (!interpret_query_s(query, name, vec, column)) return;
	temp_name = name;
	name += ".table";
	char* file_name = new char[name.size() + 1];
	for (i = 0; i < name.size(); i++){
		file_name[i] = name.at(i);
	}
	file_name[i] = '\0';
	tables_txt2.open(file_name, std::fstream::app);
	//get the info from the select clause
	vec = this->select_query(tables_txt2, vec, temp_name, column);
	tables_txt2.close();
	
	delete [] file_name;
	
	for (int i = 0; i < vec.size(); i++){
		std::cout << vec.at(i) << '\n';
	}
	
	this->query_where = 0;
}

void DataBase::delete_data(str query){
	str name, result, column, temp_name;
	str_vec vec;
	txt_file outfile;
	int i;
	result.clear();
	
	if (!interpret_query_d(query, name, vec, column)) return;
	temp_name = name;
	temp_name = temp_name + "_temp.table"; //to create name_temp.table
	
	char* file_temp = new char[temp_name.size() + 1]; //data will be temporarily stored there
	char* file_name = new char[name.size() + 1];
	for (i = 0; i < temp_name.size(); i++){
		file_temp[i] = temp_name.at(i);
	}
	file_temp[i] = '\0';
	outfile.open(file_temp);
	
	temp_name = name;
	
	name += ".table";
	for (i = 0; i < name.size(); i++){
		file_name[i] = name.at(i);
	}
	file_name[i] = '\0';
	tables_txt2.open(file_name, std::fstream::app);
	//copy to a temp file all values but deleted one
	this->delete_query(tables_txt2, outfile, vec, temp_name, column); //PRETTY MUCH the same as select_query
	tables_txt2.close();
	outfile.close();
	
	remove(file_name); //removing old data
	std::rename(file_temp, file_name); //renaming so name.table still exists with the new data
	//std::rename(file_name, file_temp); //renaming so name.table still exists with the new data
	
	delete [] file_name;
	delete [] file_temp;
	
	std::cout << "Valores eliminados.\n";
	
	this->query_where = 0;
}

void DataBase::update_data(str query){
	str name, result, column, temp_name;
	str_vec columns, values;
	txt_file outfile;
	int i;
	result.clear();
	
	if (!interpret_query_u(query, name, values, column, columns)) return;
	temp_name = name;
	temp_name = temp_name + "_temp.table"; //to create name_temp.table
	
	char* file_temp = new char[temp_name.size() + 1]; //data will be temporarily stored there
	char* file_name = new char[name.size() + 1];
	for (i = 0; i < temp_name.size(); i++){
		file_temp[i] = temp_name.at(i);
	}
	file_temp[i] = '\0';
	outfile.open(file_temp);
	
	temp_name = name;
	
	name += ".table";
	for (i = 0; i < name.size(); i++){
		file_name[i] = name.at(i);
	}
	file_name[i] = '\0';
	tables_txt2.open(file_name, std::fstream::app);
	//copy to a temp file all values but deleted one
	this->update_query(tables_txt2, outfile, columns, values, temp_name, column); //PRETTY MUCH the same as delete_query
	tables_txt2.close();
	outfile.close();
	
	remove(file_name); //removing old data
	std::rename(file_temp, file_name); //renaming so name.table still exists with the new data
	
	delete [] file_name;
	delete [] file_temp;
	
	std::cout << "Valores actualizados.\n";
	
	this->query_where = 0;
}

u_int DataBase::finding_atribute_type(str type_name, str table_name, int& pos){
	//pos will store the number of the column at the file 
	//say we're looking for the "ABCD" column, and data is stored like "AHD,ACB,ABCD,AHD"
	//pos will save the value 2
	read_file tables_file;
	tables_file.open("tables.rlpa");
	str temp, temp2;
	while(! tables_file.eof() ){
		getline(tables_file, temp);
		//std::cout << "table_name: " << table_name << " temp: " << temp << std::endl;
		if (temp == table_name) break; //we've found the table we want to look at
	}
	pos = 0;
	while(! tables_file.eof() ){
		temp2.clear();
		int i = 0;
		getline(tables_file, temp);
		if (temp[0] == '-') return -1;
		//for(i = 0; i < type_name.size(); i++){
		while(temp[i] != ' '){
			temp2 += temp[i++];
		}
		if (temp2 == type_name){
			i++; //temp[i] should be the letter of the type
			if (temp[i] == 'I') return 0; //it is an integer!
			else if (temp[i] == 'V') return 1; //it is a varchar!
			else return 2; //it is a date!
		}
		pos++;
	}
	
}

str_vec DataBase::select_query(read_file& file, str_vec columns, str name, str column){
	str temp, temp2, temp3, temp_name, vchar_value_found, vchar_val_to_compare;
	str_vec res;
	uint_vec types (columns.size() );
	u_int type;
	int pos = -1, i; //so if there's not a WHERE clause, the IF will never begin
	LL value_found, val_to_compare;
	read_file getting_columns;
	bool broke = 0, last_col = 0;
	
	temp_name = name + ".table";
	char* file_name = new char[temp_name.size() + 1];
	for (i = 0; i < temp_name.size(); i++){
		file_name[i] = temp_name.at(i);
	}
	file_name[i] = '\0';
	
	getting_columns.open(file_name); //copy of file
	
	delete [] file_name;
	temp_name.clear();
	temp.clear();
	
	if (columns.at(0) == "*"){
		if (this->query_where){ //finding the atributes
			getline(getting_columns, temp2);
			for(i = 0; i < temp2.size(); i++){
				if (temp2.at(i) == ',') {
				//std::cout << "values_to_compare.at(0) is: " << this->values_to_compare.at(0) << std::endl;
					if (temp == column ){
						type = finding_atribute_type(temp, name, pos);//finding atribute type: 0->INTEGER, 1->VARCHAR(N), 2->DATE
						broke = 1;
						break;
					//pos will store the number of column we have to check at the table
					} //else
					temp.clear();
				} else {
					temp += temp2.at(i);
				}
			}
			if (!broke){
				if (temp == column ){
					type = finding_atribute_type(temp, name, pos);//finding atribute type: 0->INTEGER, 1->VARCHAR(N), 2->DATE
				}
			}
			}
		bool first_line = true;
		while (! file.eof() ){
			temp2.clear();
			getline(file, temp2);
			temp.clear();
			int position = 0;
			temp_name.clear();
			last_col = 0;
			for(i = 0; i < temp2.size(); i++){
				if ( temp2.at(i) == ',' ) {
					temp3 = temp_name;
					if (pos == position){
						last_col = 1;
						if (type == 0){ //do the cast to the type it is
							value_found = stringToLL(temp3);
							val_to_compare = stringToLL(values_to_compare.at(0) );
							this->query_where = 1;
							if (this->comparator == 0){
								if (value_found < val_to_compare) to_insert = 1;
							}
							else if (this->comparator == 1){
								if (value_found > val_to_compare) to_insert = 1;
							}
							else {
								if (value_found == val_to_compare){
									to_insert = 1;
								}
							}
						} else if (type == 1){
							vchar_value_found = temp3;
							vchar_val_to_compare = values_to_compare.at(0);
							if (this->comparator == 0){
								if (vchar_value_found < vchar_val_to_compare) to_insert = 1;
							}
							else if (this->comparator == 1){
								if (vchar_value_found > vchar_val_to_compare) to_insert = 1;
							}
							else {
								if (vchar_value_found == vchar_val_to_compare) to_insert = 1;
							}
						} else {
							; //same as above but with date
						}
					
					//do the respective comparison with this->comparator and the value
					//THIS COMPARATOR: 0 <, 1 >, 2 =
					//for now, the value is only this->values_to_compare.at(0)
					}
					position++;
					temp += ' ';
					temp3.clear();
					temp_name.clear();
				} else {
					temp += temp2.at(i);
					temp_name += temp2.at(i);
				}
			}
			if (! last_col ){ //lines to 579 to 620 (aprox)
				temp3 = temp_name;
				if (pos == position){
					last_col = 1;
					if (type == 0){ //do the cast to the type it is
						value_found = stringToLL(temp3);
						val_to_compare = stringToLL(values_to_compare.at(0) );
						this->query_where = 1;
						if (this->comparator == 0){
							if (value_found < val_to_compare) to_insert = 1;
						}
						else if (this->comparator == 1){
							if (value_found > val_to_compare) to_insert = 1;
						}
						else {
							if (value_found == val_to_compare){
								to_insert = 1;
							}
						}
					} else if (type == 1){
						vchar_value_found = temp3;
						vchar_val_to_compare = values_to_compare.at(0);
						if (this->comparator == 0){
							if (vchar_value_found < vchar_val_to_compare) to_insert = 1;
						}
						else if (this->comparator == 1){
							if (vchar_value_found > vchar_val_to_compare) to_insert = 1;
						}
						else {
							if (vchar_value_found == vchar_val_to_compare) to_insert = 1;
						}
					} else {
						; //same as above but with date
					}
				}
				
			}
			if (temp.empty() ){
				first_line = false;
				continue;
			}
			if (! this->query_where || first_line) res.push_back(temp);
			if (this->query_where && this->to_insert) res.push_back(temp);
			this->to_insert = 0;
			first_line = false;
		}
	} else { //common case
		; 
	}
	return res;
}

void DataBase::delete_query(read_file& file, txt_file& outfile, str_vec columns, str name, str column){
	str temp, temp2, temp3, temp_name, vchar_value_found, vchar_val_to_compare;
	str_vec res;
	uint_vec types (columns.size() );
	u_int type;
	int pos = -1, i; //so if there's not a WHERE clause, the IF will never begin
	LL value_found, val_to_compare;
	read_file getting_columns;
	bool broke = 0, last_col = 0;
	
	temp_name = name + ".table";
	char* file_name = new char[temp_name.size() + 1];
	for (i = 0; i < temp_name.size(); i++){
		file_name[i] = temp_name.at(i);
	}
	file_name[i] = '\0';
	
	getting_columns.open(file_name); //copy of file
	
	delete [] file_name;
	temp_name.clear();
	temp.clear();
	
	//if (this->query_where){ //finding the atributes
		getline(getting_columns, temp2);
		for(i = 0; i < temp2.size(); i++){
			if (temp2.at(i) == ',') {
				//std::cout << "values_to_compare.at(0) is: " << this->values_to_compare.at(0) << std::endl;
				if (temp == column ){
					type = finding_atribute_type(temp, name, pos);//finding atribute type: 0->INTEGER, 1->VARCHAR(N), 2->DATE
					broke = 1;
					break;
					//pos will store the number of column we have to check at the table
				} //else
				temp.clear();
			} else {
				temp += temp2.at(i);
			}
		}
	if (!broke){
		if (temp == column ){
			type = finding_atribute_type(temp, name, pos);//finding atribute type: 0->INTEGER, 1->VARCHAR(N), 2->DATE
		}
	}
	//}
	bool first_line = true;
	while (! file.eof() ){
		temp2.clear();
		getline(file, temp2);
		temp.clear();
		int position = 0;
		temp_name.clear();
		last_col = 0;
		for(i = 0; i < temp2.size(); i++){
			if ( temp2.at(i) == ',' ) {
				temp3 = temp_name;
				if (pos == position){
					last_col = 1;
					if (type == 0){ //do the cast to the type it is
						value_found = stringToLL(temp3);
						val_to_compare = stringToLL(values_to_compare.at(0) );
						this->query_where = 1;
						if (this->comparator == 0){
							if (value_found < val_to_compare) to_insert = 1;
						}
						else if (this->comparator == 1){
							if (value_found > val_to_compare) to_insert = 1;
						}
						else {
							if (value_found == val_to_compare){
								to_insert = 1;
							}
						}
					} else if (type == 1){
						vchar_value_found = temp3;
						vchar_val_to_compare = values_to_compare.at(0);
						if (this->comparator == 0){
							if (vchar_value_found < vchar_val_to_compare) to_insert = 1;
						}
						else if (this->comparator == 1){
							if (vchar_value_found > vchar_val_to_compare) to_insert = 1;
						}
						else {
							if (vchar_value_found == vchar_val_to_compare) to_insert = 1;
						}
					} else {
						; //same as above but with date
					}
					
					//do the respective comparison with this->comparator and the value
					//THIS COMPARATOR: 0 <, 1 >, 2 =
					//for now, the value is only this->values_to_compare.at(0)
				}
				position++;
				temp += ',';
				temp3.clear();
				temp_name.clear();
			} else {
				temp += temp2.at(i);
				temp_name += temp2.at(i);
			}
		}
		if (! last_col ){ //lines to 579 to 620 (aprox)
			temp3 = temp_name;
			if (pos == position){
				last_col = 1;
				if (type == 0){ //do the cast to the type it is
					value_found = stringToLL(temp3);
					val_to_compare = stringToLL(values_to_compare.at(0) );
					this->query_where = 1;
					if (this->comparator == 0){
						if (value_found < val_to_compare) to_insert = 1;
					}
					else if (this->comparator == 1){
						if (value_found > val_to_compare) to_insert = 1;
					}
					else {
						if (value_found == val_to_compare){
							to_insert = 1;
						}
					}
				} else if (type == 1){
					vchar_value_found = temp3;
					vchar_val_to_compare = values_to_compare.at(0);
					if (this->comparator == 0){
						if (vchar_value_found < vchar_val_to_compare) to_insert = 1;
					}
					else if (this->comparator == 1){
						if (vchar_value_found > vchar_val_to_compare) to_insert = 1;
					}
					else {
						if (vchar_value_found == vchar_val_to_compare) to_insert = 1;
					}
				} else {
					; //same as above but with date
				}
			}
				
		}
		if (first_line)outfile << temp << std::endl;
		if ( ! this->to_insert && !first_line) outfile << temp << std::endl;
		this->to_insert = 0;
		first_line = false;
	}
}

void DataBase::update_query(read_file& file, txt_file& outfile, str_vec columns, str_vec values, str name, str column){
	str temp, temp2, temp3, temp_name, vchar_value_found, vchar_val_to_compare;
	str_vec res;
	uint_vec types (columns.size() ); //types: if boolean operators are used
	uint_vec positions (columns.size()); //positions: positions of the columns in the table
	u_int type, j;
	u_int it;
	int pos = -1, i; //so if there's not a WHERE clause, the IF will never begin
	LL value_found, val_to_compare;
	read_file getting_columns;
	bool broke = 0, last_col = 0;
	
	temp_name = name + ".table";
	char* file_name = new char[temp_name.size() + 1];
	for (i = 0; i < temp_name.size(); i++){
		file_name[i] = temp_name.at(i);
	}
	file_name[i] = '\0';
	
	getting_columns.open(file_name); //copy of file
	
	delete [] file_name;
	temp_name.clear();
	temp.clear();
	
	//if (this->query_where){ //finding the atributes
	getline(getting_columns, temp2);
	for(i = 0; i < temp2.size(); i++){
		if (temp2.at(i) == ',') {
			//std::cout << "values_to_compare.at(0) is: " << this->values_to_compare.at(0) << std::endl;
			if (temp == column ){
				type = finding_atribute_type(temp, name, pos);//finding atribute type: 0->INTEGER, 1->VARCHAR(N), 2->DATE
				broke = 1;
				break;
				//pos will store the number of column we have to check at the table
			} //else
			temp.clear();
		} else {
			temp += temp2.at(i);
		}
	}
	if (!broke){
		if (temp == column ){
			type = finding_atribute_type(temp, name, pos);//finding atribute type: 0->INTEGER, 1->VARCHAR(N), 2->DATE
		}
	}
	temp.clear();
	for (it = 0; it < columns.size(); it++){ //getting positions of columns to update
		broke = 0;
		int k = 0;
		for(j = 0; j < temp2.size(); j++){
			if (temp2.at(j) == ',') {
				//std::cout << "values_to_compare.at(0) is: " << this->values_to_compare.at(0) << std::endl;
				if (temp == columns.at(it) ){
					positions.at(it) = k; //keeping a relation: columns[it] position is in positions[it]
					broke = 1;
					break;
					//pos will store the number of column we have to check at the table
				} //else
				temp.clear();
				k++;
			} else {
				temp += temp2.at(j);
			}
		}
		if (!broke){
			if (temp == columns.at(it) ){
				positions.at(it) = k;
			}
		}
	}
	bool first_line = true;
	std::cout << "type is: " << type << std::endl;
	std::cout << "pos is: " << pos << std::endl;
	while (! file.eof() ){
		temp2.clear();
		getline(file, temp2);
		temp.clear();
		int position = 0;
		temp_name.clear();
		last_col = 0;
		for(i = 0; i < temp2.size(); i++){ //getting the lines of data
			if ( temp2.at(i) == ',' ) {
				temp3 = temp_name;
				if (pos == position){
					last_col = 1;
					if (type == 0){ //do the cast to the type it is
						value_found = stringToLL(temp3);
						val_to_compare = stringToLL(values_to_compare.at(0) );
						this->query_where = 1;
						if (this->comparator == 0){ //in this case: to_insert = to_update
							if (value_found < val_to_compare) to_insert = 1;
						}
						else if (this->comparator == 1){
							if (value_found > val_to_compare) to_insert = 1;
						}
						else {
							if (value_found == val_to_compare){
								to_insert = 1;
							}
						}
					} else if (type == 1){
						vchar_value_found = temp3;
						vchar_val_to_compare = values_to_compare.at(0);
						if (this->comparator == 0){
							if (vchar_value_found < vchar_val_to_compare) to_insert = 1;
						}
						else if (this->comparator == 1){
							if (vchar_value_found > vchar_val_to_compare) to_insert = 1;
						}
						else {
							if (vchar_value_found == vchar_val_to_compare) to_insert = 1;
						}
					} else {
						; //same as above but with date
					}
					
					//do the respective comparison with this->comparator and the value
					//THIS COMPARATOR: 0 <, 1 >, 2 =
					//for now, the value is only this->values_to_compare.at(0)
				}
				position++;
				temp += ',';
				temp3.clear();
				temp_name.clear();
			} else {
				temp += temp2.at(i);
				temp_name += temp2.at(i);
			}
		}
		if (! last_col ){ //lines to 579 to 620 (aprox)
			temp3 = temp_name;
			if (pos == position){
				last_col = 1;
				if (type == 0){ //do the cast to the type it is
					value_found = stringToLL(temp3);
					val_to_compare = stringToLL(values_to_compare.at(0) );
					this->query_where = 1;
					if (this->comparator == 0){
						if (value_found < val_to_compare) to_insert = 1;
					}
					else if (this->comparator == 1){
						if (value_found > val_to_compare) to_insert = 1;
					}
					else {
						if (value_found == val_to_compare){
							to_insert = 1;
						}
					}
				} else if (type == 1){
					vchar_value_found = temp3;
					vchar_val_to_compare = values_to_compare.at(0);
					if (this->comparator == 0){
						if (vchar_value_found < vchar_val_to_compare) to_insert = 1;
					}
					else if (this->comparator == 1){
						if (vchar_value_found > vchar_val_to_compare) to_insert = 1;
					}
					else {
						if (vchar_value_found == vchar_val_to_compare) to_insert = 1;
					}
				} else {
					; //same as above but with date
				}
			}
			
		}
		if (first_line)outfile << temp << std::endl;
		if ( this->to_insert && !first_line){
			temp = updateRow(temp, positions, values);
			outfile << temp << std::endl;
		} else if (!first_line) outfile << temp << std::endl;
			
		this->to_insert = 0;
		first_line = false;
	}
}
