#include "Menu.h"

Menu::Menu(DataBase db) {
	this->db = db;
	this->currentMenu = 0;
}

void Menu::main_menu(){
	str num;
	std::cout << "Bienvenido al gestor, digite el numero segun lo que desee hacer:\n";
	std::cout << "1. Crear tablas\n";
	std::cout << "2. Insertar tablas\n";
	std::cout << "3. SOON\n";
	std::cout << "100. Salir\n";
	std::getline(std::cin, num);
	this->currentMenu = stringToUint(num);
	switch(this->currentMenu){
	case 1:
		menu_1();
		break;
	case 2:
		menu_2();
	case 100:
		std::cout << "Nos vemos pronto !!!\n";
		exit(18); //code 18: user has exited the dbms
	default:
		std::cout << "Numero no reconocido. Vuelva a intentarlo.\n";
		main_menu();
		break;
	}
}

void Menu::menu_1(){
	str query;
	std::cout << "Ingrese la sentencia de crear tabla.\n";
	std::cout << "Tener cuidado con la sintaxis (revisar sintaxis.txt).\n";
	std::getline(std::cin, query); //Working now
	db.create_table(query);
	std::cout << "Regresando al menu principal.\n";
	main_menu();
}

void Menu::menu_2(){
	str query;
	std::cout << "Ingrese la sentencia de insertar datos.\n";
	std::cout << "Tener cuidado con la sintaxis (revisar sintaxis.txt).\n";
	std::getline(std::cin, query);
	db.insert_row(query);
	std::cout << "Regresando al menu principal.\n";
	main_menu();
}

