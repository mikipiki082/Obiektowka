#pragma once

#include <string>
#include <vector>
#include "Lekcja.h"

class Modul {
private:
    int idModulu;
    std::string tytul;
    std::vector<Lekcja> listaLekcji;

public:
    // Konstruktor
    Modul(int id, std::string tytul);

    // Gettery
    int pobierzId() const;
    std::string pobierzTytul() const;
    std::vector<Lekcja> pobierzLekcje() const;

    // Metody
    void dodajLekcje(Lekcja lekcja);
    bool usunLekcje(int idLekcji);
};