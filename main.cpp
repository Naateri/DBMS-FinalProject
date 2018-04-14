#include<iostream>
#include "Menu.h"

int main (int argc, char *argv[]) {
	
	DataBase mainDB;
	
	Menu myMenu(mainDB);
	
	myMenu.main_menu();
	
	return 0;
}

