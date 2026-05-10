#include <iostream>
#include "tablero.h"
#include "Detective.h"
using namespace std;
int n = 10;
void juego(string& nombre) {
    char opc;
    int pun = 0;
    Detective d(nombre);
    do {
        Tablero t;
        cout << nombre << ", Tu puntaje actual es " << pun << endl;
        t.mostrar(d);
        cout << "Moverse (w/a/s/d), 0 para salir: ";
        cin >> opc;
        pun++;

        if (opc != '0')
            d.movimiento(opc);
    }while (opc != '0');
};
void menu() {
    int op;
    do {
        cout <<"--- MENU ---" << endl;
        cout <<"1. Empezar Juego" << endl;
        cout <<"2. Ver Partidas anteriores" << endl;
        cout <<"3. ver puntjes altos" << endl;
        cout <<"0. salir" << endl;
        cout <<"Ingrese una opcion: " << endl;
        cin >> op;
        switch (op) {
            case 0:
                exit(0);
            case 1: {
                string nombre;
                cout << "Ingrese tu nombre: ";
                cin >> nombre;
                juego(nombre);
                break;
            }
            case 2:
                break;
            case 3:
                break;
            default:
                cout << "ingrese una opcion valida" << endl;
        }

    }while(op != 0);
};

int main() {
    menu();
}