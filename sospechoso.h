//
// Created by USUARIO on 12/05/2026.
//
#ifndef SOSPECHOSO_H
#define SOSPECHOSO_H

#include <string>
#include <vector>

using namespace std;

class Sospechoso {
private:
    string nombre;
    string estatura;      // "alto", "bajo", "mediano"
    string colorCabello;  // "negro", "rubio", "castaño", "rojo"
    string colorPiel;     // "claro", "moreno", "oscuro"
    string formaNariz;    // "recta", "aguileña", "respingada"
    bool zurdo;

public:
    Sospechoso();
    Sospechoso(const string& nombre, const string& estatura,
               const string& cabello, const string& piel,
               const string& nariz, bool zurdo);

    string getNombre() const;
    string getEstatura() const;
    string getColorCabello() const;
    string getColorPiel() const;
    string getFormaNariz() const;
    bool esZurdo() const;

    // Devuelve todos los atributos como strings (ej. "alto", "cabello rojo", "zurdo")
    vector<string> obtenerAtributos() const;

    // Verifica si el sospechoso posee un atributo dado
    bool tieneAtributo(const string& atributo) const;
};

#endif