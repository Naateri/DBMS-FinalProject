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
-Create table with columns:
	-ID INTEGER (INCREMENTAL)
	-NOMBRE VARCHAR(15)
	-APELLIDO VARCHAR(20)
	-EDAD INTEGER
	-FECHA DATE
	FILLED WITH 100K
	ANOTHER ONE WITH 1M
	INSERTS, DELETES, UPDATES
	(objective: 24/04/2018 6:59 pm)
-Loading the already created tables to tables_vec (objective: 19/04/2018 11:30 pm) //NOT REALLY A PRIORITY RIGHT NOW
-INSERT(n) (objective: 22/04/2018 11:59 pm)
-All of UPDATE (objective: 23/04/2018 9:59 pm)

DUE DATE: 05/05/2018 10:00 am

Secondary Objective: work AT LEAST one daily hour here

DONE:
-CREATE TABLE syntax 
-Store correctly the data_types and names to each data type for Integer and date
-Adding n atributes to a table
-Adding the table metadata to hdd (at tables.rlpa)
-Recognize VARCHAR(n) and store it somehow within the table data (reason why we have char_name pairs) (done: 16/04/2018 10:49 pm)
-Creating a new .table file per table created (where the data will be stored) (stored csv-like) (done: 17/04/2018 8:33 am)
-When inserting the table to "tables.rlpa", to NOT delete the previous inserted Data (done: 17/04/2018 8:46 am)
-INSERT INTO syntax and actually inserting data (done: 18/04/2018 11:08 pm)
-SELECT * FROM TABLE (done: 18/04/2018 11:42 pm)
-WHERE CLAUSE (done: 19/04/2018 6:08 pm)
-DELETE (done: 20/04/2018 11:00 pm)

**/
