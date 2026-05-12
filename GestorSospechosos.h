//
// Created by USUARIO on 12/05/2026.
//
#ifndef GESTORSOSPECHOSOS_H
#define GESTORSOSPECHOSOS_H

#include <unordered_map>
#include <string>
#include <vector>
#include <set>
#include "Sospechoso.h"

using namespace std;

class GestorSospechosos {
private:
    unordered_map<string, Sospechoso> tablaHash;
    string culpableNombre;
    set<string> atributosRevelados;

    // Genera un sospechoso con atributos aleatorios
    Sospechoso generarSospechosoAleatorio(const string& nombre);

public:
    // Crea 8 sospechosos desde una lista predefinida
    void generarSospechosos();

    // Muestra la tabla hash (tecla 'S' en el juego)
    void mostrarSospechosos() const;

    // Revela un atributo nuevo del culpable (llamar al recoger pista o testigo)
    void revelarAtributoAleatorio();

    // Busca un sospechoso por nombre (O(1) promedio)
    const Sospechoso* buscarSospechoso(const string& nombre) const;

    // Verifica si el nombre acusado es el culpable
    bool esCulpable(const string& acusado) const;

    // Métodos auxiliares
    string getCulpableNombre() const;
    const set<string>& getAtributosRevelados() const;
};

#endif