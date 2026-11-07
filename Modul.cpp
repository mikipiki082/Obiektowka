#include "Modul.h"

// Konstruktor
Modul::Modul(int id, std::string tytul) {
    idModulu = id;
    this->tytul = tytul;
}

// Gettery
int Modul::pobierzId() const {
    return idModulu;
}

std::string Modul::pobierzTytul() const {
    return tytul;
}

std::vector<Lekcja> Modul::pobierzLekcje() const {
    return listaLekcji;
}

// Dodawanie lekcji
void Modul::dodajLekcje(Lekcja lekcja) {
    listaLekcji.push_back(lekcja);
}

// Usuwanie lekcji
bool Modul::usunLekcje(int idLekcji) {
    for (int i = 0; i < listaLekcji.size(); i++) {
        if (listaLekcji[i].pobierzId() == idLekcji) {
            listaLekcji.erase(listaLekcji.begin() + i);
            return true;
        }
    }

    return false;
}