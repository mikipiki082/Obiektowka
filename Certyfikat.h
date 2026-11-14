#pragma once

#include <string>

class Certyfikat {
private:
    int idCertyfikatu;
    int idKursu;
    std::string tytulKursu;
    int idKursanta;
    std::string dataWydania;

public:
    // Konstruktor
    Certyfikat(int idCertyfikatu, int idKursu, std::string tytulKursu,
               int idKursanta, std::string dataWydania);

    // Gettery
    int pobierzId() const;
    int pobierzIdKursu() const;
    std::string pobierzTytulKursu() const;
    int pobierzIdKursanta() const;
    std::string pobierzDateWydania() const;
};