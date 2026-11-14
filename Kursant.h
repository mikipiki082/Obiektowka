#pragma once

#include <string>
#include "Uzytkownik.h"
#include "Konto.h"

// Dziedziczenie
class Kursant : public Uzytkownik {
private:
    Konto konto;

public:
    // Konstruktor
    Kursant(int id, std::string imie, std::string nazwisko);

    // Gettery
    Konto& pobierzKonto();
    const Konto& pobierzKonto() const;

    // Polimorfizm
    std::string pobierzRole() const override;
};