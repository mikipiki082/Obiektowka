#include "Lekcja.h"

// Konstruktor
Lekcja::Lekcja(int id, std::string tytul) {
    idLekcji = id;
    this->tytul = tytul;
}

// Gettery
int Lekcja::pobierzId() const {
    return idLekcji;
}

std::string Lekcja::pobierzTytul() const {
    return tytul;
}

// Dodawanie materialu
void Lekcja::dodajMaterial(std::string material) {
    materialy.push_back(material);
}

// Usuwanie materialu
bool Lekcja::usunMaterial(std::string material) {
    for (int i = 0; i < materialy.size(); i++) {
        if (materialy[i] == material) {
            materialy.erase(materialy.begin() + i);
            return true;
        }
    }

    return false;
}

// Zwracanie listy materialow
std::vector<std::string> Lekcja::pobierzMaterialy() const {
    return materialy;
}