//
// Created by Maria-Camila on 8/05/2026.
//

#include "Tablero.h"
#include "Detective.h"

Tablero::Tablero() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0 || i == n-1 || j == 0 || j == n-1)
                tablero.push_back('#');
            else
                tablero.push_back('o');
        }
        tablero.push_back(' ');
    }
}

void Tablero::colocarEn(int x, int y, char simbolo) {
    auto it = tablero.begin();
    int objetivo = x * (n + 1) + y;

    for (int i = 0; i < objetivo; i++) {
        it++;
    }

    *it = simbolo;
}

void Tablero::mostrarTablero() {
    for (char i : tablero) {
        if (i == ' ' ){
            cout << endl;
        }else {
            cout << i;
            cout << " ";
        }
    }
}

void Tablero::mostrar(Detective &d) {
    colocarEn(d.dxAnterior, d.dyAnterior, 'o');
    colocarEn(d.dx, d.dy, 'D');
    mostrarTablero();
}

Tablero::~Tablero() {
}
