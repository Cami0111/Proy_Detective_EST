

#ifndef PROY_DETECTIVE_H
#define PROY_DETECTIVE_H
#include <iostream>
#include <string>
#include "Tablero.h"
#include "Detective.h"

extern int n;
using namespace std;

class Detective {
private:
    string nombre;
public:
    int dx, dy;
    int dxAnterior, dyAnterior;
    Detective(string nombre);

    string getNombre();

    void mostrarDetective(Tablero& t);
    void movimiento(char mov);
};


#endif //PROY_DETECTIVE_H