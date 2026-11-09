#pragma once

#include <string>
#include "Uzytkownik.h"

// Dziedziczenie
class Wykladowca : public Uzytkownik {
private:
    std::string idPracownika;
    std::string dataZatrudnienia;
    double pensja;

public:
    // Konstruktor
    Wykladowca(int id, std::string imie, std::string nazwisko,
               std::string idPracownika, std::string dataZatrudnienia,
               double pensja);

    // Gettery
    std::string pobierzIdPracownika() const;

    // Polimorfizm
    std::string pobierzRole() const override;
};