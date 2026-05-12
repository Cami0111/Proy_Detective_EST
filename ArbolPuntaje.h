#ifndef ARBOLPUNTAJES_H
#define ARBOLPUNTAJES_H

#include <string>
using namespace std;

struct NodoPuntaje {
    string nombre;
    int puntaje;
    NodoPuntaje* izq;
    NodoPuntaje* der;

    NodoPuntaje(const string& n, int p)
        : nombre(n), puntaje(p), izq(nullptr), der(nullptr) {}
};

class ArbolPuntajes {
private:
    NodoPuntaje* raiz;

    NodoPuntaje* insertarNodo(NodoPuntaje* nodo, const string& nombre, int puntaje);
    NodoPuntaje* eliminarNodo(NodoPuntaje* nodo, int puntaje, const string& nombre);
    NodoPuntaje* minNodo(NodoPuntaje* nodo) const;
    NodoPuntaje* buscarPorNombre(NodoPuntaje* nodo, const string& nombre) const;
    void inOrder(NodoPuntaje* nodo) const;
    void destruir(NodoPuntaje* nodo);

public:
    ArbolPuntajes();
    ~ArbolPuntajes();

    void insertar(const string& nombre, int puntaje);
    int buscar(const string& nombre) const;
    void mostrarRanking() const;
};

#endif
