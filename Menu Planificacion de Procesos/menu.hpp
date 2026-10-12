#ifndef MENU_HPP
#define MENU_HPP

#include <iostream>

using namespace std;

class menu {
private:
	void mostrarOpciones();

	int leerOpcion();
public:
	void ejecutar();
};
#endif