#include "Kurs.h"

// Konstruktor
Kurs::Kurs(int id, std::string tytul) {
    idKursu = id;
    this->tytul = tytul;
}

// Gettery
int Kurs::pobierzId() const {
    return idKursu;
}

std::string Kurs::pobierzTytul() const {
    return tytul;
}

std::vector<Modul> Kurs::pobierzModuly() const {
    return listaModulow;
}

// Liczba wszystkich lekcji w kursie
int Kurs::pobierzLiczbeLekcji() const {
    int liczbaLekcji = 0;

    for (int i = 0; i < listaModulow.size(); i++) {
        liczbaLekcji += listaModulow[i].pobierzLekcje().size();
    }

    return liczbaLekcji;
}

// Dodawanie modulu
void Kurs::dodajModul(Modul modul) {
    listaModulow.push_back(modul);
}

// Usuwanie modulu
bool Kurs::usunModul(int idModulu) {
    for (int i = 0; i < listaModulow.size(); i++) {
        if (listaModulow[i].pobierzId() == idModulu) {
            listaModulow.erase(listaModulow.begin() + i);
            return true;
        }
    }

    return false;
}

 // Dodawanie lekcji do modulu
bool Kurs::dodajLekcje(int idModulu, Lekcja lekcja) {
    for (Modul& modul : listaModulow) {
        if (modul.pobierzId() == idModulu) {
            modul.dodajLekcje(lekcja);
            return true;
        }
    }

    return false;
}
