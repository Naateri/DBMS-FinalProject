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
