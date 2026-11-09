#include "Postep.h"

// Konstruktor
Postep::Postep(const Kurs* kurs) {
    this->kurs = kurs;
}

// Gettery
int Postep::pobierzIdKursu() const {
    return kurs->pobierzId();
}

int Postep::pobierzLiczbeUkonczonychModulow() const {
    int liczba = 0;

    for (Modul modul : kurs->pobierzModuly()) {
        if (czyModulUkonczony(modul.pobierzId())) {
            liczba++;
        }
    }

    return liczba;
}

// Sprawdzanie ukonczonej lekcji
bool Postep::czyLekcjaUkonczona(int idLekcji) const {
    for (int id : ukonczoneLekcje) {
        if (id == idLekcji) {
            return true;
        }
    }

    return false;
}

// Sprawdzanie ukonczonego modulu
bool Postep::czyModulUkonczony(int idModulu) const {
    for (Modul modul : kurs->pobierzModuly()) {
        if (modul.pobierzId() == idModulu) {
            if (modul.pobierzLekcje().empty()) {
                return false;
            }

            for (Lekcja lekcja : modul.pobierzLekcje()) {
                if (!czyLekcjaUkonczona(lekcja.pobierzId())) {
                    return false;
                }
            }

            return true;
        }
    }

    return false;
}

// Sprawdzanie dostepnosci modulu
bool Postep::czyModulOdblokowany(int idModulu) const {
    std::vector<Modul> moduly = kurs->pobierzModuly();

    for (int i = 0; i < moduly.size(); i++) {
        if (moduly[i].pobierzId() == idModulu) {
            if (i == 0) {
                return true;
            }

            return czyModulUkonczony(moduly[i - 1].pobierzId());
        }
    }

    return false;
}

// Ukonczenie lekcji
bool Postep::ukonczLekcje(int idLekcji) {
    for (Modul modul : kurs->pobierzModuly()) {
        for (Lekcja lekcja : modul.pobierzLekcje()) {
            if (lekcja.pobierzId() == idLekcji) {
                if (!czyModulOdblokowany(modul.pobierzId())) {
                    return false;
                }

                if (czyLekcjaUkonczona(idLekcji)) {
                    return false;
                }

                ukonczoneLekcje.push_back(idLekcji);
                return true;
            }
        }
    }

    return false;
}

// Sprawdzanie ukonczenia kursu
bool Postep::czyKursUkonczony() const {
    std::vector<Modul> moduly = kurs->pobierzModuly();

    if (moduly.empty()) {
        return false;
    }

    for (Modul modul : moduly) {
        if (!czyModulUkonczony(modul.pobierzId())) {
            return false;
        }
    }

    return true;
}

// Obliczanie procentu ukonczenia kursu
double Postep::obliczProcentUkonczenia() const {
    int wszystkieLekcje = kurs->pobierzLiczbeLekcji();

    if (wszystkieLekcje == 0) {
        return 0.0;
    }

    return 100.0 * ukonczoneLekcje.size() / wszystkieLekcje;
}