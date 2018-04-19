#include "functions.h"

u_int stringToUint(str a){
	u_int ret;
	ss convi(a);
	convi >> ret;
	return ret;
}

void print_vec(strp_vec vec, char_name_vec cvec){
	int j = 0;
	for(int i = 0; i < vec.size(); i++){
		std::cout << "Tipo de dato: " << vec.at(i).first << '\n';
		std::cout << "Nombre de la columna: " << vec.at(i).second << '\n';
		if (vec.at(i).first == "VARCHAR" ){
			std::cout << "El VARCHAR es de " << cvec.at(j).second << std::endl;
			j++;
		}
		std::cout << std::endl;
	}

}

void writeInsert(txt_file& file, str_vec t){
	for (int i = 0; i < t.size(); i++){
		if (i != t.size() - 1) file << t.at(i) << ',';
		else file << t.at(i) << '\n';
	}
	//file << '\n';
}

str_vec select_query(read_file& file, str_vec columns){
	str temp, temp2;
	str_vec res;
	if (columns.at(0) == "*"){
		while (! file.eof() ){
			temp2.clear();
			getline(file, temp2);
			temp.clear();
			for(int i = 0; i < temp2.size(); i++){
				if (temp2.at(i) == ',') {
					temp += ' ';
				} else temp += temp2.at(i);
			}
			res.push_back(temp);
		}
	} else { //common case
		; 
	}
	return res;
}
