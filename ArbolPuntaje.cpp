#include "ArbolPuntaje.h"
#include <iostream>
using namespace std;

ArbolPuntajes::ArbolPuntajes() : raiz(nullptr) {}

ArbolPuntajes::~ArbolPuntajes() {
    destruir(raiz);
}

void ArbolPuntajes::destruir(NodoPuntaje* nodo) {
    if (!nodo) return;
    destruir(nodo->izq);
    destruir(nodo->der);
    delete nodo;
}

NodoPuntaje* ArbolPuntajes::insertarNodo(NodoPuntaje* nodo, const string& nombre, int puntaje) {
    if (!nodo) return new NodoPuntaje(nombre, puntaje);

    bool goLeft = (puntaje < nodo->puntaje) ||
                  (puntaje == nodo->puntaje && nombre < nodo->nombre);

    if (goLeft)
        nodo->izq = insertarNodo(nodo->izq, nombre, puntaje);
    else
        nodo->der = insertarNodo(nodo->der, nombre, puntaje);

    return nodo;
}

NodoPuntaje* ArbolPuntajes::minNodo(NodoPuntaje* nodo) const {
    while (nodo->izq) nodo = nodo->izq;
    return nodo;
}

NodoPuntaje* ArbolPuntajes::eliminarNodo(NodoPuntaje* nodo, int puntaje, const string& nombre) {
    if (!nodo) return nullptr;

    bool goLeft = (puntaje < nodo->puntaje) ||
                  (puntaje == nodo->puntaje && nombre < nodo->nombre);
    bool goRight = (puntaje > nodo->puntaje) ||
                   (puntaje == nodo->puntaje && nombre > nodo->nombre);

    if (goLeft) {
        nodo->izq = eliminarNodo(nodo->izq, puntaje, nombre);
    } else if (goRight) {
        nodo->der = eliminarNodo(nodo->der, puntaje, nombre);
    } else {
        if (!nodo->izq) {
            NodoPuntaje* temp = nodo->der;
            delete nodo;
            return temp;
        }
        if (!nodo->der) {
            NodoPuntaje* temp = nodo->izq;
            delete nodo;
            return temp;
        }
        NodoPuntaje* sucesor = minNodo(nodo->der);
        nodo->nombre = sucesor->nombre;
        nodo->puntaje = sucesor->puntaje;
        nodo->der = eliminarNodo(nodo->der, sucesor->puntaje, sucesor->nombre);
    }
    return nodo;
}

NodoPuntaje* ArbolPuntajes::buscarPorNombre(NodoPuntaje* nodo, const string& nombre) const {
    if (!nodo) return nullptr;
    if (nodo->nombre == nombre) return nodo;
    NodoPuntaje* found = buscarPorNombre(nodo->izq, nombre);
    if (found) return found;
    return buscarPorNombre(nodo->der, nombre);
}

void ArbolPuntajes::inOrder(NodoPuntaje* nodo) const {
    if (!nodo) return;
    inOrder(nodo->izq);
    cout << "  " << nodo->nombre << " -> " << nodo->puntaje << " movimientos\n";
    inOrder(nodo->der);
}

void ArbolPuntajes::insertar(const string& nombre, int puntaje) {
    NodoPuntaje* existente = buscarPorNombre(raiz, nombre);
    if (existente) {
        if (puntaje >= existente->puntaje) return;
        raiz = eliminarNodo(raiz, existente->puntaje, existente->nombre);
    }
    raiz = insertarNodo(raiz, nombre, puntaje);
}

int ArbolPuntajes::buscar(const string& nombre) const {
    NodoPuntaje* nodo = buscarPorNombre(raiz, nombre);
    if (!nodo) return -1;
    return nodo->puntaje;
}

void ArbolPuntajes::mostrarRanking() const {
    cout << "\n====== RANKING HISTORICO ======\n";
    cout << "  (menor puntaje = mejor detective)\n";
    if (!raiz) {
        cout << "  No hay registros aun.\n";
    } else {
        inOrder(raiz);
    }
    cout << "===============================\n";
}
