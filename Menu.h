#ifndef MENU_H
#define MENU_H
//types included at db.h
#include "db.h"
#include "functions.h"

class Menu {
private:
	DataBase db;
	u_short currentMenu;
	void menu_1();
public:
	Menu(DataBase db);
	void main_menu();
};
#endif

