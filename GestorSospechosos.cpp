//
// Created by USUARIO on 12/05/2026.
//
#include "GestorSospechosos.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

// Lista de nombres posibles (se toman los primeros 8)
static const vector<string> NOMBRES = {
    "Carlos", "Diana", "Eduardo", "Fernanda", "Gonzalo", "Hilda",
    "Isabel", "Javier", "Lucia", "Miguel"
};

// Atributos posibles
static const vector<string> ESTATURAS = {"alto", "bajo", "mediano"};
static const vector<string> CABELLOS = {"negro", "rubio", "castaño", "rojo"};
static const vector<string> PIELES = {"claro", "moreno", "oscuro"};
static const vector<string> NARICES = {"recta", "aguileña", "respingada"};

// Generador aleatorio con semilla única
static mt19937 generador(chrono::steady_clock::now().time_since_epoch().count());

Sospechoso GestorSospechosos::generarSospechosoAleatorio(const string& nombre) {
    uniform_int_distribution<int> distEst(0, ESTATURAS.size()-1);
    uniform_int_distribution<int> distCab(0, CABELLOS.size()-1);
    uniform_int_distribution<int> distPiel(0, PIELES.size()-1);
    uniform_int_distribution<int> distNariz(0, NARICES.size()-1);
    uniform_int_distribution<int> distZurdo(0, 1);

    return Sospechoso(nombre,
                      ESTATURAS[distEst(generador)],
                      CABELLOS[distCab(generador)],
                      PIELES[distPiel(generador)],
                      NARICES[distNariz(generador)],
                      distZurdo(generador) == 1);
}

void GestorSospechosos::generarSospechosos() {
    tablaHash.clear();
    // Tomamos los primeros 8 nombres
    for (int i = 0; i < 8 && i < (int)NOMBRES.size(); ++i) {
        Sospechoso s = generarSospechosoAleatorio(NOMBRES[i]);
        tablaHash[NOMBRES[i]] = s;
    }
    // Elegir culpable al azar entre los 8
    uniform_int_distribution<int> dist(0, 7);
    culpableNombre = NOMBRES[dist(generador)];
    atributosRevelados.clear();
}

void GestorSospechosos::mostrarSospechosos() const {
    cout << "\n--- SOSPECHOSOS (Tabla Hash) ---\n";
    for (const auto& par : tablaHash) {
        const Sospechoso& s = par.second;
        cout << s.getNombre() << " | atributos confirmados: ";
        bool primero = true;
        for (const string& attr : atributosRevelados) {
            if (s.tieneAtributo(attr)) {
                if (!primero) cout << ", ";
                cout << attr;
                primero = false;
            }
        }
        if (primero) cout << "-";
        cout << endl;
    }
    cout << "--------------------------------\n";
}

void GestorSospechosos::revelarAtributoAleatorio() {
    if (tablaHash.empty()) return;
    auto it = tablaHash.find(culpableNombre);
    if (it == tablaHash.end()) return;
    const Sospechoso& culpable = it->second;
    vector<string> todosAtributos = culpable.obtenerAtributos();

    // Filtrar los que aún no se han revelado
    vector<string> nuevos;
    for (const string& attr : todosAtributos) {
        if (atributosRevelados.find(attr) == atributosRevelados.end()) {
            nuevos.push_back(attr);
        }
    }
    if (nuevos.empty()) return; // ya no hay más atributos por revelar

    uniform_int_distribution<int> dist(0, nuevos.size()-1);
    string elegido = nuevos[dist(generador)];
    atributosRevelados.insert(elegido);
    cout << "\n[NUEVA PISTA] Atributo del culpable: " << elegido << endl;
}

const Sospechoso* GestorSospechosos::buscarSospechoso(const string& nombre) const {
    auto it = tablaHash.find(nombre);
    if (it != tablaHash.end()) return &(it->second);
    return nullptr;
}

bool GestorSospechosos::esCulpable(const string& acusado) const {
    return acusado == culpableNombre;
}

string GestorSospechosos::getCulpableNombre() const {
    return culpableNombre;
}

const set<string>& GestorSospechosos::getAtributosRevelados() const {
    return atributosRevelados;
}