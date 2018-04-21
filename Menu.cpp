#include "Menu.h"

Menu::Menu(DataBase db) {
	this->db = db;
	this->currentMenu = 0;
}

void Menu::main_menu(){
	str num;
	std::cout << "Bienvenido al gestor, digite el numero segun lo que desee hacer:\n";
	std::cout << "1. Crear tablas\n";
	std::cout << "2. Insertar fila de datos\n";
	std::cout << "3. Seleccionar datos\n";
	std::cout << "4. Eliminar datos\n";
	std::cout << "5. SOON\n";
	std::cout << "100. Salir\n";
	std::getline(std::cin, num);
	this->currentMenu = stringToUint(num);
	switch(this->currentMenu){
	case 1:
		menu_1();
		break;
	case 2:
		menu_2();
		break;
	case 3:
		menu_3();
		break;
	case 4:
		menu_4();
		break;
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

void Menu::menu_3(){
	str query;
	std::cout << "Ingrese la sentencia de seleccionar datos.\n";
	std::cout << "Tener cuidado con la sintaxis (revisar sintaxis.txt).\n";
	std::getline(std::cin, query);
	db.select_data(query);
	std::cout << "Regresando al menu principal.\n";
	main_menu();
}

void Menu::menu_4(){
	str query;
	std::cout << "Ingrese la sentencia de eliminar datos.\n";
	std::cout << "Tener cuidado con la sintaxis (revisar sintaxis.txt).\n";
	std::getline(std::cin, query);
	db.delete_data(query);
	std::cout << "Regresando al menu principal.\n";
	main_menu();
}
