#include "Certyfikat.h"

// Konstruktor
Certyfikat::Certyfikat(int idCertyfikatu, int idKursu,
                       std::string tytulKursu, int idKursanta,
                       std::string dataWydania) {
    this->idCertyfikatu = idCertyfikatu;
    this->idKursu = idKursu;
    this->tytulKursu = tytulKursu;
    this->idKursanta = idKursanta;
    this->dataWydania = dataWydania;
}

// Gettery
int Certyfikat::pobierzId() const {
    return idCertyfikatu;
}

int Certyfikat::pobierzIdKursu() const {
    return idKursu;
}

std::string Certyfikat::pobierzTytulKursu() const {
    return tytulKursu;
}

int Certyfikat::pobierzIdKursanta() const {
    return idKursanta;
}

std::string Certyfikat::pobierzDateWydania() const {
    return dataWydania;
}