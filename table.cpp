#include "table.h"

Table::Table(str name, strp_vec& vec, uint_vec nums){
	this->name = name;
	Data *temp = new Data(nums.at(0), nums.at(1), nums.at(2), vec);
	this->t_data = temp;
}

str Table::getName(){
	return this->name;
}

void Table::desc(){
	int camps;
	camps = this->t_data->n + this->t_data->v + this->t_data->d;
	std::cout << "Tabla: " << this->name << '\n';
	std::cout << "Hay " << camps << " atributos.\n"; 
	print_vec(this->t_data->names);
}

