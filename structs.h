#include "types.h"
#include "functions.h"

struct VCHAR{
	u_int n; //size of char
	char* V_CHAR;
	VCHAR(){
		this->n = 0;
		this->V_CHAR = new char[0];
	}
	VCHAR(u_int n){
		this->n = n;
		this->V_CHAR = new char[n+1];
		V_CHAR[n] = '\0';
	}
};

struct Data{
	LL* NUMBER;
	VCHAR* VARCHAR;
	char** DATE;
	strp_vec names; //pair: type, name
	char_name_vec vchars;
	u_int n, v, d;
	Data(){
		;
	}
	Data( u_int n, u_int v, u_int d, strp_vec names, char_name_vec vchars ){ //n = amount of numbers, v = amount of chars, d = amount of dates
		this->NUMBER = new LL[n];
		this->VARCHAR = new VCHAR[v];
		this->DATE = new char*[d];
		this->names = names;
		this->vchars = vchars;
		this->n = n;
		this->v = v;
		this->d = d;
	}
	void print_info(){
		print_vec(names, vchars);
	}
};
