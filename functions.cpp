#include "functions.h"

u_int stringToUint(str a){
	u_int ret;
	ss convi(a);
	convi >> ret;
	return ret;
}

void print_vec(strp_vec vec){
	for(int i = 0; i < vec.size(); i++){
		std::cout << "Tipo de dato: " << vec.at(i).first << '\n';
		std::cout << "Nombre de la columna: " << vec.at(i).second << '\n';
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
