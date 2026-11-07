#pragma once

#include <string>
#include <vector>
#include "Modul.h"

class Kurs {
private:
    int idKursu;
    std::string tytul;
    std::vector<Modul> listaModulow;

public:
    // Konstruktor
    Kurs(int id, std::string tytul);

    // Gettery
    int pobierzId() const;
    std::string pobierzTytul() const;
    std::vector<Modul> pobierzModuly() const;
    int pobierzLiczbeLekcji() const;

    // Metody
    void dodajModul(Modul modul);
    bool usunModul(int idModulu);
    bool dodajLekcje(int idModulu, Lekcja lekcja);
};