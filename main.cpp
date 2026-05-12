#include <iostream>
#include "tablero.h"
#include "Detective.h"
#include "GestorSospechosos.h"

using namespace std;

int n = 10;

void juego(string& nombre) {
    char opc;
    int pun = 0;
    Detective d(nombre);

    GestorSospechosos gestor;
    gestor.generarSospechosos();

    do {
        Tablero t;
        cout << nombre << ", Tu puntaje actual es " << pun << endl;
        t.mostrar(d);
        cout << "Moverse (w/a/s/d) | S: Ver sospechosos | X: Usar pista | 0: Salir: ";
        cin >> opc;

        if (opc == 'S' || opc == 's') {
            gestor.mostrarSospechosos();
            continue;
        }

        if (opc == 'X' || opc == 'x') {
            cout << "Funcionalidad de usar pista aun no implementada.\n";
            continue;
        }

        if (opc != '0') {
            d.movimiento(opc);
            pun++;

            // Simulacion: cada 3 movimientos revela un atributo (cambiar despues)
            static int cont = 0;
            cont++;
            if (cont % 3 == 0) {
                gestor.revelarAtributoAleatorio();
            }
        }

    } while (opc != '0');

    cout << "\n¿Deseas acusar a alguien? (s/n): ";
    char acusar;
    cin >> acusar;
    if (acusar == 's' || acusar == 'S') {
        gestor.mostrarSospechosos();
        cout << "Escribe el nombre del sospechoso a acusar: ";
        string acusado;
        cin >> acusado;
        if (gestor.esCulpable(acusado)) {
            cout << "¡CASO RESUELTO! " << acusado << " era el culpable.\n";
            cout << "Puntaje final: " << pun << " movimientos.\n";
        } else {
            cout << "Acusaste a " << acusado << ", pero no es el culpable.\n";
            cout << "Caso fracasado. Puntaje penalizado: " << pun * 2 << "\n";
        }
    }
}

void menu() {
    int op;
    do {
        cout << "--- MENU ---" << endl;
        cout << "1. Empezar Juego" << endl;
        cout << "2. Ver Partidas anteriores" << endl;
        cout << "3. Ver puntajes altos" << endl;
        cout << "0. Salir" << endl;
        cout << "Ingrese una opcion: ";
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
                cout << "Opcion no valida" << endl;
        }
    } while (op != 0);
}

int main() {
    menu();
    return 0;
}