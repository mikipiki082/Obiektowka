#include "Kursant.h"

// Konstruktor
Kursant::Kursant(int id, std::string imie, std::string nazwisko)
    : Uzytkownik(id, imie, nazwisko) {
}

// Gettery
Konto& Kursant::pobierzKonto() {
    return konto;
}

const Konto& Kursant::pobierzKonto() const {
    return konto;
}

// Polimorfizm
std::string Kursant::pobierzRole() const {
    return "Kursant";
}