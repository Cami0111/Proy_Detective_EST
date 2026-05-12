//
// Created by USUARIO on 12/05/2026.
//
#include "Sospechoso.h"

Sospechoso::Sospechoso() : estatura(""), colorCabello(""), colorPiel(""), formaNariz(""), zurdo(false) {}

Sospechoso::Sospechoso(const string& nombre, const string& estatura,
                       const string& cabello, const string& piel,
                       const string& nariz, bool zurdo)
    : nombre(nombre), estatura(estatura), colorCabello(cabello),
      colorPiel(piel), formaNariz(nariz), zurdo(zurdo) {}

string Sospechoso::getNombre() const { return nombre; }
string Sospechoso::getEstatura() const { return estatura; }
string Sospechoso::getColorCabello() const { return colorCabello; }
string Sospechoso::getColorPiel() const { return colorPiel; }
string Sospechoso::getFormaNariz() const { return formaNariz; }
bool Sospechoso::esZurdo() const { return zurdo; }

vector<string> Sospechoso::obtenerAtributos() const {
    vector<string> attrs;
    if (estatura == "alto") attrs.push_back("alto");
    else if (estatura == "bajo") attrs.push_back("bajo");
    else if (estatura == "mediano") attrs.push_back("mediano");

    if (colorCabello == "rojo") attrs.push_back("cabello rojo");
    else if (colorCabello == "negro") attrs.push_back("cabello negro");
    else if (colorCabello == "rubio") attrs.push_back("cabello rubio");
    else if (colorCabello == "castaño") attrs.push_back("cabello castaño");

    if (colorPiel == "moreno") attrs.push_back("moreno");
    else if (colorPiel == "claro") attrs.push_back("piel clara");
    else if (colorPiel == "oscuro") attrs.push_back("piel oscura");

    if (formaNariz == "aguileña") attrs.push_back("nariz aguileña");
    else if (formaNariz == "recta") attrs.push_back("nariz recta");
    else if (formaNariz == "respingada") attrs.push_back("nariz respingada");

    if (zurdo) attrs.push_back("zurdo");
    return attrs;
}

bool Sospechoso::tieneAtributo(const string& atributo) const {
    vector<string> misAttrs = obtenerAtributos();
    for (const auto& a : misAttrs) {
        if (a == atributo) return true;
    }
    return false;
}