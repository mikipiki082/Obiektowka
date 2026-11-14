#pragma once

#include <vector>
#include "Kurs.h"
#include "Postep.h"
#include "Certyfikat.h"

class Konto {
private:
    std::vector<const Kurs*> aktywneKursy;
    std::vector<Postep> postepy;
    std::vector<Certyfikat> certyfikaty;

public:
    // Konstruktor
    Konto();

    // Gettery
    std::vector<const Kurs*> pobierzAktywneKursy() const;
    const Postep* pobierzPostep(int idKursu) const;
    Postep* pobierzPostep(int idKursu);
    std::vector<Postep> pobierzPostepy() const;
    std::vector<Certyfikat> pobierzCertyfikaty() const;

    // Metody
    bool dodajKurs(const Kurs* kurs);
    bool usunKurs(int idKursu);
    void dodajCertyfikat(Certyfikat certyfikat);
    bool czyMaCertyfikat(int idKursu) const;
};
