#include "Detective.h"
#include "Tablero.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Detective::Detective(string nombre) {
    srand(time(0));
    this->nombre = nombre;
    dx = rand() % (n-2) + 1;
    dy = rand() % (n-2) + 1;
    dxAnterior = dx;
    dyAnterior = dy;

}

string Detective::getNombre() {
    return nombre;
}

void Detective::mostrarDetective(Tablero &t) {
    t.colocarEn(dx, dy, 'D');
}

void Detective::movimiento(char mov) {
    dxAnterior= dx;
    dyAnterior= dy;
    int nuevoDx = dx;
    int nuevoDy = dy;

    switch(mov) {
        case 'w': nuevoDx--; break;
        case 's': nuevoDx++; break;
        case 'a': nuevoDy--; break;
        case 'd': nuevoDy++; break;
    }

    if (nuevoDx > 0 && nuevoDx < n-1 &&
        nuevoDy > 0 && nuevoDy < n-1) {
        dx = nuevoDx;
        dy = nuevoDy;
        }
}
