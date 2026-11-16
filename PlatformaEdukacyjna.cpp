#include "PlatformaEdukacyjna.h"
#include <ctime>

// Konstruktor
PlatformaEdukacyjna::PlatformaEdukacyjna() {
    nastepneIdKursu = 1;
    nastepneIdModulu = 1;
    nastepneIdLekcji = 1;
    nastepneIdCertyfikatu = 1;
}

// Wyszukiwanie kursu
Kurs* PlatformaEdukacyjna::znajdzKurs(int idKursu) const {
    for (const auto& kurs : katalogKursow) {
        if (kurs->pobierzId() == idKursu) {
            return kurs.get();
        }
    }
    return nullptr;
}

// Wyszukiwanie kursanta
Kursant* PlatformaEdukacyjna::znajdzKursanta(int idKursanta) const {
    for (const auto& kursant : listaKursantow) {
        if (kursant->pobierzId() == idKursanta) {
            return kursant.get();
        }
    }
    return nullptr;
}

// Sprawdzanie wykladowcy
bool PlatformaEdukacyjna::czyWykladowcaIstnieje(std::string idPracownika) const {
    for (const auto& wykladowca : listaWykladowcow) {
        if (wykladowca->pobierzIdPracownika() == idPracownika) {
            return true;
        }
    }
    return false;
}

// Sprawdzanie zapisow
bool PlatformaEdukacyjna::czyKursMaZapisy(int idKursu) const {
    for (const auto& kursant : listaKursantow) {
        if (kursant->pobierzKonto().pobierzPostep(idKursu) != nullptr) {
            return true;
        }
    }
    return false;
}

// Dodawanie kursanta
bool PlatformaEdukacyjna::dodajKursanta(
    int id, std::string imie, std::string nazwisko) {
    if (znajdzKursanta(id) != nullptr) {
        return false;
    }
    listaKursantow.push_back(std::make_unique<Kursant>(id, imie, nazwisko));
    return true;
}

// Dodawanie wykladowcy
bool PlatformaEdukacyjna::dodajWykladowce(
    int id, std::string imie, std::string nazwisko,
    std::string idPracownika, std::string dataZatrudnienia, double pensja) {
    if (czyWykladowcaIstnieje(idPracownika)) {
        return false;
    }
    for (const auto& wykladowca : listaWykladowcow) {
        if (wykladowca->pobierzId() == id) {
            return false;
        }
    }
    listaWykladowcow.push_back(std::make_unique<Wykladowca>(
        id, imie, nazwisko, idPracownika, dataZatrudnienia, pensja));
    return true;
}

// Dodawanie kursu
bool PlatformaEdukacyjna::dodajKurs(std::string idPracownika, Kurs kurs) {
    if (!czyWykladowcaIstnieje(idPracownika) ||
        znajdzKurs(kurs.pobierzId()) != nullptr) {
        return false;
    }
    katalogKursow.push_back(std::make_unique<Kurs>(kurs));
    return true;
}

// Usuwanie kursu
bool PlatformaEdukacyjna::usunKurs(std::string idPracownika, int idKursu) {
    if (!czyWykladowcaIstnieje(idPracownika)) {
        return false;
    }

    if (znajdzKurs(idKursu) == nullptr) {
        return false;
    }

    // Usuwanie zapisow i postepow
    for (const auto& kursant : listaKursantow) {
        kursant->pobierzKonto().usunKurs(idKursu);
    }

    // Usuwanie kursu z platformy
    for (int i = 0; i < katalogKursow.size(); i++) {
        if (katalogKursow[i]->pobierzId() == idKursu) {
            katalogKursow.erase(katalogKursow.begin() + i);
            return true;
        }
    }

    return false;
}

// Dodawanie modulu
bool PlatformaEdukacyjna::dodajModul(
    std::string idPracownika, int idKursu, Modul modul) {
    Kurs* kurs = znajdzKurs(idKursu);
    if (!czyWykladowcaIstnieje(idPracownika) ||
        kurs == nullptr || czyKursMaZapisy(idKursu)) {
        return false;
    }
    for (const Modul& stary : kurs->pobierzModuly()) {
        if (stary.pobierzId() == modul.pobierzId()) {
            return false;
        }
    }
    kurs->dodajModul(modul);
    return true;
}

// Dodawanie lekcji
bool PlatformaEdukacyjna::dodajLekcje(
    std::string idPracownika, int idKursu, int idModulu, Lekcja lekcja) {
    Kurs* kurs = znajdzKurs(idKursu);
    if (!czyWykladowcaIstnieje(idPracownika) ||
        kurs == nullptr || czyKursMaZapisy(idKursu)) {
        return false;
    }
    for (const Modul& modul : kurs->pobierzModuly()) {
        for (const Lekcja& stara : modul.pobierzLekcje()) {
            if (stara.pobierzId() == lekcja.pobierzId()) {
                return false;
            }
        }
    }
    return kurs->dodajLekcje(idModulu, lekcja);
}

// Automatyczne tworzenie kursu
int PlatformaEdukacyjna::utworzKurs(
    std::string idPracownika, std::string tytul) {
    while (znajdzKurs(nastepneIdKursu) != nullptr) {
        nastepneIdKursu++;
    }
    Kurs kurs(nastepneIdKursu, tytul);
    if (!dodajKurs(idPracownika, kurs)) {
        return -1;
    }
    return nastepneIdKursu++;
}

// Automatyczne tworzenie modulu
int PlatformaEdukacyjna::utworzModul(
    std::string idPracownika, int idKursu, std::string tytul) {
    Kurs* kurs = znajdzKurs(idKursu);
    if (kurs == nullptr) {
        return -1;
    }
    bool zajete = true;
    while (zajete) {
        zajete = false;
        for (const Modul& modul : kurs->pobierzModuly()) {
            if (modul.pobierzId() == nastepneIdModulu) {
                nastepneIdModulu++;
                zajete = true;
                break;
            }
        }
    }
    Modul modul(nastepneIdModulu, tytul);
    if (!dodajModul(idPracownika, idKursu, modul)) {
        return -1;
    }
    return nastepneIdModulu++;
}

// Automatyczne tworzenie lekcji
int PlatformaEdukacyjna::utworzLekcje(
    std::string idPracownika, int idKursu, int idModulu,
    std::string tytul, std::string material) {
    Kurs* kurs = znajdzKurs(idKursu);
    if (kurs == nullptr) {
        return -1;
    }
    bool zajete = true;
    while (zajete) {
        zajete = false;
        for (const Modul& modul : kurs->pobierzModuly()) {
            for (const Lekcja& lekcja : modul.pobierzLekcje()) {
                if (lekcja.pobierzId() == nastepneIdLekcji) {
                    nastepneIdLekcji++;
                    zajete = true;
                    break;
                }
            }
            if (zajete) break;
        }
    }
    Lekcja lekcja(nastepneIdLekcji, tytul);
    lekcja.dodajMaterial(material);
    if (!dodajLekcje(idPracownika, idKursu, idModulu, lekcja)) {
        return -1;
    }
    return nastepneIdLekcji++;
}

// Zapisywanie na kurs
bool PlatformaEdukacyjna::zapiszNaKurs(int idKursanta, int idKursu) {
    Kursant* kursant = znajdzKursanta(idKursanta);
    Kurs* kurs = znajdzKurs(idKursu);
    if (kursant == nullptr || kurs == nullptr) {
        return false;
    }
    return kursant->pobierzKonto().dodajKurs(kurs);
}

// Ukonczenie lekcji
bool PlatformaEdukacyjna::ukonczLekcje(
    int idKursanta, int idKursu, int idLekcji) {
    Kursant* kursant = znajdzKursanta(idKursanta);
    Kurs* kurs = znajdzKurs(idKursu);
    if (kursant == nullptr || kurs == nullptr) {
        return false;
    }
    Konto& konto = kursant->pobierzKonto();
    Postep* postep = konto.pobierzPostep(idKursu);
    if (postep == nullptr || !postep->ukonczLekcje(idLekcji)) {
        return false;
    }

    // Generowanie certyfikatu
    if (postep->czyKursUkonczony() && !konto.czyMaCertyfikat(idKursu)) {
        std::time_t teraz = std::time(nullptr);
        char data[11] = "";
        std::strftime(data, sizeof(data), "%Y-%m-%d", std::localtime(&teraz));
        Certyfikat certyfikat(nastepneIdCertyfikatu, idKursu,
                             kurs->pobierzTytul(), idKursanta, data);
        konto.dodajCertyfikat(certyfikat);
        nastepneIdCertyfikatu++;
    }
    return true;
}

// Statystyki kursu
std::vector<Postep> PlatformaEdukacyjna::pobierzStatystykiKursu(
    std::string idPracownika, int idKursu) const {
    std::vector<Postep> wyniki;
    if (!czyWykladowcaIstnieje(idPracownika) || znajdzKurs(idKursu) == nullptr) {
        return wyniki;
    }
    for (const auto& kursant : listaKursantow) {
        const Postep* postep = kursant->pobierzKonto().pobierzPostep(idKursu);
        if (postep != nullptr) {
            wyniki.push_back(*postep);
        }
    }
    return wyniki;
}

// Statystyki kursanta
std::vector<Postep> PlatformaEdukacyjna::pobierzStatystykiKursanta(
    std::string idPracownika, int idKursanta) const {
    if (!czyWykladowcaIstnieje(idPracownika)) {
        return {};
    }
    Kursant* kursant = znajdzKursanta(idKursanta);
    if (kursant == nullptr) {
        return {};
    }
    return kursant->pobierzKonto().pobierzPostepy();
}

// Gettery
const Kursant* PlatformaEdukacyjna::pobierzKursanta(int idKursanta) const {
    return znajdzKursanta(idKursanta);
}

const Kurs* PlatformaEdukacyjna::pobierzKurs(int idKursu) const {
    return znajdzKurs(idKursu);
}

std::vector<const Kurs*> PlatformaEdukacyjna::pobierzKursy() const {
    std::vector<const Kurs*> kursy;
    for (const auto& kurs : katalogKursow) {
        kursy.push_back(kurs.get());
    }
    return kursy;
}

std::vector<const Kursant*> PlatformaEdukacyjna::pobierzKursantow() const {
    std::vector<const Kursant*> kursanci;
    for (const auto& kursant : listaKursantow) {
        kursanci.push_back(kursant.get());
    }
    return kursanci;
}

std::vector<const Wykladowca*> PlatformaEdukacyjna::pobierzWykladowcow() const {
    std::vector<const Wykladowca*> wykladowcy;
    for (const auto& wykladowca : listaWykladowcow) {
        wykladowcy.push_back(wykladowca.get());
    }
    return wykladowcy;
}