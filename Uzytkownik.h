#pragma once

#include <string>

class Uzytkownik {
protected:
    int id;
    std::string imie;
    std::string nazwisko;

public:
    // Konstruktor
    Uzytkownik(int id, std::string imie, std::string nazwisko);

    // Destruktor wirtualny
    virtual ~Uzytkownik();

    // Gettery
    int pobierzId() const;
    std::string pobierzImie() const;
    std::string pobierzNazwisko() const;

    // Metoda wirtualna - polimorfizm
    virtual std::string pobierzRole() const = 0;
};