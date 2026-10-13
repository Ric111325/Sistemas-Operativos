#ifndef MENU_HPP
#define MENU_HPP

#include <iostream>
#include "dqueue.hpp"
#include "PlanNoExpro.hpp"

using namespace std;

class menu {
private:
    dqueue cola_procesos;

   
    FIFO obj_fifo;
    SJF obj_sjf;

    void mostrarOpciones();
    int leerOpcion();
    void capturarProcesos();

public:
    void ejecutar();
};

#endif