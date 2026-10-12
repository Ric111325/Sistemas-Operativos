#include "dqueue.hpp"

dqueue::node::node(int x){
    
    dat = x;
    nxt = nullptr;
}

dqueue::~dqueue(){

    node *temp;

    while (start != nullptr) {

        temp = start;
        start = start->next();
        delete temp;
    }
}

void dqueue::print(){
    node *temp = start;

    cout << "Elementos de la cola: ";

    while (temp != nullptr) {

        cout << temp->data() << " ";
        temp = temp->next();
    }

    cout << endl;
}