#include "types.h"
struct VCHAR{
	u_int n; //size of char
	char* V_CHAR;
	VCHAR(u_int n){
		this->n = n;
		this->V_CHAR = new char[n+1];
		V_CHAR[n] = '\0';
	}
};

struct Data{
	LL* NUMBER;
	char** VARCHAR;
	char** DATE;
	str_vec names;
	Data(){
		;
	}
	Data( u_int n, u_int v, u_int d ){ //n = amount of numbers, v = amount of chars, d = amount of dates
		this->NUMBER = new LL[n];
		this->VARCHAR = new char*[v];
		this->DATE = new char*[d];
	}
};
