#include "Uzytkownik.h"

// Konstruktor
Uzytkownik::Uzytkownik(int id, std::string imie, std::string nazwisko) {
    this->id = id;
    this->imie = imie;
    this->nazwisko = nazwisko;
}

// Destruktor
Uzytkownik::~Uzytkownik() {
}

// Gettery
int Uzytkownik::pobierzId() const {
    return id;
}

std::string Uzytkownik::pobierzImie() const {
    return imie;
}

std::string Uzytkownik::pobierzNazwisko() const {
    return nazwisko;
}