#pragma once

#include <vector>
#include "Kurs.h"

class Postep {
private:
    const Kurs* kurs;
    std::vector<int> ukonczoneLekcje;

public:
    // Konstruktor
    Postep(const Kurs* kurs);

    // Gettery
    int pobierzIdKursu() const;
    int pobierzLiczbeUkonczonychModulow() const;

    // Metody
    bool ukonczLekcje(int idLekcji);
    bool czyLekcjaUkonczona(int idLekcji) const;
    bool czyModulOdblokowany(int idModulu) const;
    bool czyModulUkonczony(int idModulu) const;
    bool czyKursUkonczony() const;
    double obliczProcentUkonczenia() const;
};