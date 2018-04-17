#include<iostream>
#include "Menu.h"


int main (int argc, char *argv[]) {
	
	DataBase mainDB;
	
	Menu myMenu(mainDB);
	
	myMenu.main_menu();
	
	return 0;
}


/**

TO-DO (thus far, will keep adding here):
-When inserting the table to "tables.rlpa", to NOT delete the previous inserted Data (objective: 17/04/2018 9:00 pm)
-Creating a new .rlpa file per table created (where the data will be stored) (objective: 17/04/2018 9:00 pm)
-Loading the already created tables to tables_vec (objective: 19/04/2018 11:30 pm)
-All of SELECT  (objective: 25/04/2018 11:30 pm)
-All of INSERT (including INSERT(n) elements) (objective: 21/04/2018 11:59 pm)
-All of DELETE (objective: 27/04/2018 11:59 pm)
-All of UPDATE (objective: 1/05/2018 8:00 pm)

DUE DATE: 05/05/2018 10:00 am

Secondary Objective: work AT LEAST one daily hour here

DONE:
-CREATE TABLE syntax 
-Store correctly the data_types and names to each data type for Integer and date
-Adding n atributes to a table
-Adding the table metadata to hdd (at tables.rlpa)
-Recognize VARCHAR(n) and store it somehow within the table data (reason why we have char_name pairs) (done: 16/04/2018 10:49 pm)

**/
