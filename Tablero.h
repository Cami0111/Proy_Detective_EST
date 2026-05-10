//
// Created by Maria-Camila on 8/05/2026.
//

#ifndef PROY_TABLERO_H
#define PROY_TABLERO_H
#include <iostream>
#include <list>



using namespace std;
extern int n;

class Detective;
class Tablero {
public:
    list<char> tablero;

    Tablero();
    void colocarEn(int x, int y, char l);;
    void mostrarTablero();

    void mostrar(Detective& d);

    ~Tablero();
};


#endif //PROY_TABLERO_H