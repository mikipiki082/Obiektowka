#include "Konto.h"

// Konstruktor
Konto::Konto() {
}

// Gettery
std::vector<const Kurs*> Konto::pobierzAktywneKursy() const {
    return aktywneKursy;
}

const Postep* Konto::pobierzPostep(int idKursu) const {
    for (const Postep& postep : postepy) {
        if (postep.pobierzIdKursu() == idKursu) {
            return &postep;
        }
    }

    return nullptr;
}

Postep* Konto::pobierzPostep(int idKursu) {
    for (Postep& postep : postepy) {
        if (postep.pobierzIdKursu() == idKursu) {
            return &postep;
        }
    }

    return nullptr;
}

std::vector<Postep> Konto::pobierzPostepy() const {
    return postepy;
}

std::vector<Certyfikat> Konto::pobierzCertyfikaty() const {
    return certyfikaty;
}

// Dodawanie kursu
bool Konto::dodajKurs(const Kurs* kurs) {
    if (kurs == nullptr) {
        return false;
    }

    if (pobierzPostep(kurs->pobierzId()) != nullptr) {
        return false;
    }

    aktywneKursy.push_back(kurs);
    postepy.push_back(Postep(kurs));

    return true;
}

// Usuwanie kursu i postepu
bool Konto::usunKurs(int idKursu) {
    bool znaleziono = false;

    for (int i = 0; i < postepy.size(); i++) {
        if (postepy[i].pobierzIdKursu() == idKursu) {
            postepy.erase(postepy.begin() + i);
            znaleziono = true;
            break;
        }
    }

    for (int i = 0; i < aktywneKursy.size(); i++) {
        if (aktywneKursy[i]->pobierzId() == idKursu) {
            aktywneKursy.erase(aktywneKursy.begin() + i);
            znaleziono = true;
            break;
        }
    }

    return znaleziono;
}

// Dodawanie certyfikatu
void Konto::dodajCertyfikat(Certyfikat certyfikat) {
    certyfikaty.push_back(certyfikat);
}

// Sprawdzanie certyfikatu
bool Konto::czyMaCertyfikat(int idKursu) const {
    for (const Certyfikat& certyfikat : certyfikaty) {
        if (certyfikat.pobierzIdKursu() == idKursu) {
            return true;
        }
    }

    return false;
}