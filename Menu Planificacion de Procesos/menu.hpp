#ifndef MENU_HPP
#define MENU_HPP

#include <iostream>
#include "dqueue.hpp"
#include "PlanNoExpro.hpp"
#include "PlanExpro.hpp"

using namespace std;

class menu {
private:
    dqueue cola_procesos;

    FIFO obj_fifo;
    SJF obj_sjf;
    Prioridad obj_prioridad; 
    RoundRobin obj_rr;

    void mostrarOpciones();
    int leerOpcion();
    void capturarProcesos();

public:
    void ejecutar();
};

#endif