#include "Wykladowca.h"

// Konstruktor
Wykladowca::Wykladowca(int id, std::string imie, std::string nazwisko,
                       std::string idPracownika,
                       std::string dataZatrudnienia, double pensja)
    : Uzytkownik(id, imie, nazwisko) {

    this->idPracownika = idPracownika;
    this->dataZatrudnienia = dataZatrudnienia;
    this->pensja = pensja;
}

// Gettery
std::string Wykladowca::pobierzIdPracownika() const {
    return idPracownika;
}

// Polimorfizm
std::string Wykladowca::pobierzRole() const {
    return "Wykladowca";
}