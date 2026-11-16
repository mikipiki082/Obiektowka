#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include "PlatformaEdukacyjna.h"

// Wczytywanie numeru
int wczytajNumer() {
    int numer;
    if (!(std::cin >> numer)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return -1;
    }
    return numer;
}

// Wczytywanie tekstu
std::string wczytajTekst() {
    std::string tekst;
    std::getline(std::cin >> std::ws, tekst);
    return tekst;
}

// Wybor wykladowcy
std::string wybierzWykladowce(const PlatformaEdukacyjna& platforma) {
    std::vector<const Wykladowca*> lista = platforma.pobierzWykladowcow();
    std::cout << "\n=== WYBOR WYKLADOWCY ===\n";
    for (int i = 0; i < lista.size(); i++) {
        std::cout << i + 1 << ". " << lista[i]->pobierzImie()
                  << " " << lista[i]->pobierzNazwisko() << "\n";
    }
    std::cout << "0. Powrot\nWybor: ";
    int numer = wczytajNumer();
    if (numer < 1 || numer > static_cast<int>(lista.size())) return "";
    return lista[numer - 1]->pobierzIdPracownika();
}

// Wybor kursanta
int wybierzKursanta(const PlatformaEdukacyjna& platforma) {
    std::vector<const Kursant*> lista = platforma.pobierzKursantow();
    std::cout << "\n=== WYBOR KURSANTA ===\n";
    for (int i = 0; i < lista.size(); i++) {
        std::cout << i + 1 << ". " << lista[i]->pobierzImie()
                  << " " << lista[i]->pobierzNazwisko() << "\n";
    }
    std::cout << "0. Powrot\nWybor: ";
    int numer = wczytajNumer();
    if (numer < 1 || numer > static_cast<int>(lista.size())) return -1;
    return lista[numer - 1]->pobierzId();
}

// Wybor kursu
const Kurs* wybierzKurs(const std::vector<const Kurs*>& kursy) {
    std::cout << "\n=== WYBOR KURSU ===\n";
    if (kursy.empty()) std::cout << "Brak kursow.\n";
    for (int i = 0; i < kursy.size(); i++) {
        std::cout << i + 1 << ". " << kursy[i]->pobierzTytul() << "\n";
    }
    std::cout << "0. Powrot\nWybor: ";
    int numer = wczytajNumer();
    if (numer < 1 || numer > static_cast<int>(kursy.size())) return nullptr;
    return kursy[numer - 1];
}

// Wybor modulu
int wybierzModul(const Kurs& kurs, const Postep* postep = nullptr) {
    std::vector<Modul> moduly = kurs.pobierzModuly();
    std::cout << "\n=== WYBOR MODULU ===\n";
    if (moduly.empty()) std::cout << "Brak modulow.\n";
    for (int i = 0; i < moduly.size(); i++) {
        std::cout << i + 1 << ". " << moduly[i].pobierzTytul();
        if (postep != nullptr &&
            !postep->czyModulOdblokowany(moduly[i].pobierzId())) {
            std::cout << " [ZABLOKOWANY]";
        }
        std::cout << "\n";
    }
    std::cout << "0. Powrot\nWybor: ";
    int numer = wczytajNumer();
    if (numer < 1 || numer > static_cast<int>(moduly.size())) return -1;
    int id = moduly[numer - 1].pobierzId();
    if (postep != nullptr && !postep->czyModulOdblokowany(id)) {
        std::cout << "Ten modul jest zablokowany.\n";
        return -1;
    }
    return id;
}

// Wybor lekcji
int wybierzLekcje(const Modul& modul, const Postep& postep) {
    std::vector<Lekcja> lekcje = modul.pobierzLekcje();
    std::cout << "\n=== WYBOR LEKCJI ===\n";
    if (lekcje.empty()) std::cout << "Brak lekcji.\n";
    for (int i = 0; i < lekcje.size(); i++) {
        std::cout << i + 1 << ". " << lekcje[i].pobierzTytul();
        if (postep.czyLekcjaUkonczona(lekcje[i].pobierzId())) {
            std::cout << " [UKONCZONA]";
        }
        std::cout << "\n";
    }
    std::cout << "0. Powrot\nWybor: ";
    int numer = wczytajNumer();
    if (numer < 1 || numer > static_cast<int>(lekcje.size())) return -1;
    return lekcje[numer - 1].pobierzId();
}

// Wyswietlanie postepow
void wyswietlPostepy(const Kursant& kursant,
                     const PlatformaEdukacyjna& platforma) {
    std::cout << "\n=== POSTEPY KURSANTA ===\n";
    std::vector<Postep> postepy = kursant.pobierzKonto().pobierzPostepy();
    if (postepy.empty()) std::cout << "Brak zapisanych kursow.\n";
    for (const Postep& postep : postepy) {
        const Kurs* kurs = platforma.pobierzKurs(postep.pobierzIdKursu());
        if (kurs != nullptr) {
            std::cout << kurs->pobierzTytul() << ": "
                      << postep.obliczProcentUkonczenia() << "% (moduly: "
                      << postep.pobierzLiczbeUkonczonychModulow() << "/"
                      << kurs->pobierzModuly().size() << ")\n";
        }
    }
}

// Menu wykladowcy
void menuWykladowcy(PlatformaEdukacyjna& platforma) {
    std::string idPracownika = wybierzWykladowce(platforma);
    if (idPracownika.empty()) return;

    int wybor = -1;
    while (wybor != 0) {
        std::cout << "\n=== PANEL WYKLADOWCY ===\n"
                  << "1. Wyswietl kursy\n"
                  << "2. Dodaj kurs\n"
                  << "3. Usun kurs\n"
                  << "4. Dodaj modul\n"
                  << "5. Dodaj lekcje\n"
                  << "6. Statystyki kursu\n"
                  << "7. Statystyki kursanta\n"
                  << "0. Powrot\nWybor: ";
        wybor = wczytajNumer();

        switch (wybor) {
            case 1: {
                std::vector<const Kurs*> kursy = platforma.pobierzKursy();
                if (kursy.empty()) std::cout << "Brak kursow.\n";
                for (const Kurs* kurs : kursy) {
                    std::cout << "- " << kurs->pobierzTytul() << "\n";
                }
                break;
            }
            case 2: {
                std::cout << "Tytul nowego kursu: ";
                std::string tytul = wczytajTekst();
                int id = platforma.utworzKurs(idPracownika, tytul);
                std::cout << (id == -1 ? "Nie udalo sie dodac kursu.\n" :
                              "Dodano kurs.\n");
                break;
            }
            case 3: {
                const Kurs* kurs = wybierzKurs(platforma.pobierzKursy());
                if (kurs == nullptr) break;
                if (platforma.usunKurs(idPracownika, kurs->pobierzId())) {
                    std::cout << "Usunieto kurs.\n";
                } else {
                    std::cout << "Nie mozna usunac kursu z zapisanymi kursantami.\n";
                }
                break;
            }
            case 4: {
                const Kurs* kurs = wybierzKurs(platforma.pobierzKursy());
                if (kurs == nullptr) break;
                int idKursu = kurs->pobierzId();
                std::cout << "Tytul nowego modulu: ";
                std::string tytul = wczytajTekst();
                int id = platforma.utworzModul(idPracownika, idKursu, tytul);
                std::cout << (id == -1 ? "Nie mozna dodac modulu.\n" :
                              "Dodano modul.\n");
                break;
            }
            case 5: {
                const Kurs* kurs = wybierzKurs(platforma.pobierzKursy());
                if (kurs == nullptr) break;
                int idModulu = wybierzModul(*kurs);
                if (idModulu == -1) break;
                std::cout << "Tytul nowej lekcji: ";
                std::string tytul = wczytajTekst();
                std::cout << "Material lekcji: ";
                std::string material = wczytajTekst();
                int id = platforma.utworzLekcje(idPracownika,
                    kurs->pobierzId(), idModulu, tytul, material);
                std::cout << (id == -1 ? "Nie mozna dodac lekcji.\n" :
                              "Dodano lekcje.\n");
                break;
            }
            case 6: {
                const Kurs* kurs = wybierzKurs(platforma.pobierzKursy());
                if (kurs == nullptr) break;
                std::vector<Postep> wyniki = platforma.pobierzStatystykiKursu(
                    idPracownika, kurs->pobierzId());
                std::cout << "\nKurs: " << kurs->pobierzTytul() << "\n";
                std::cout << "Liczba kursantow: " << wyniki.size() << "\n";
                for (const Kursant* kursant : platforma.pobierzKursantow()) {
                    const Postep* postep =
                        kursant->pobierzKonto().pobierzPostep(kurs->pobierzId());
                    if (postep != nullptr) {
                        std::cout << kursant->pobierzImie() << " "
                                  << kursant->pobierzNazwisko() << ": "
                                  << postep->obliczProcentUkonczenia() << "%\n";
                    }
                }
                break;
            }
            case 7: {
                int idKursanta = wybierzKursanta(platforma);
                if (idKursanta == -1) break;
                const Kursant* kursant = platforma.pobierzKursanta(idKursanta);
                if (kursant != nullptr) {
                    wyswietlPostepy(*kursant, platforma);
                }
                break;
            }
            case 0:
                break;
            default:
                std::cout << "Nieprawidlowy wybor.\n";
        }
    }
}

// Menu kursanta
void menuKursanta(PlatformaEdukacyjna& platforma) {
    int idKursanta = wybierzKursanta(platforma);
    if (idKursanta == -1) return;

    int wybor = -1;
    while (wybor != 0) {
        std::cout << "\n=== PANEL KURSANTA ===\n"
                  << "1. Wyswietl kursy\n"
                  << "2. Zapisz sie na kurs\n"
                  << "3. Wyswietl moduly i lekcje\n"
                  << "4. Ukoncz lekcje\n"
                  << "5. Moje postepy\n"
                  << "6. Moje certyfikaty\n"
                  << "0. Powrot\nWybor: ";
        wybor = wczytajNumer();
        const Kursant* kursant = platforma.pobierzKursanta(idKursanta);

        switch (wybor) {
            case 1: {
                std::vector<const Kurs*> kursy = platforma.pobierzKursy();
                if (kursy.empty()) std::cout << "Brak kursow.\n";
                for (const Kurs* kurs : kursy) {
                    std::cout << "- " << kurs->pobierzTytul() << "\n";
                }
                break;
            }
            case 2: {
                const Kurs* kurs = wybierzKurs(platforma.pobierzKursy());
                if (kurs == nullptr) break;
                if (platforma.zapiszNaKurs(idKursanta, kurs->pobierzId())) {
                    std::cout << "Zapisano na kurs.\n";
                } else {
                    std::cout << "Nie udalo sie zapisac.\n";
                }
                break;
            }
            case 3: {
                const Kurs* kurs = wybierzKurs(kursant->pobierzKonto().pobierzAktywneKursy());
                if (kurs == nullptr) break;
                const Postep* postep = kursant->pobierzKonto().pobierzPostep(kurs->pobierzId());
                for (const Modul& modul : kurs->pobierzModuly()) {
                    std::cout << "\nModul: " << modul.pobierzTytul();
                    if (!postep->czyModulOdblokowany(modul.pobierzId())) {
                        std::cout << " [ZABLOKOWANY]\n";
                        continue;
                    }
                    std::cout << "\n";
                    for (const Lekcja& lekcja : modul.pobierzLekcje()) {
                        std::cout << "  " << lekcja.pobierzTytul();
                        if (postep->czyLekcjaUkonczona(lekcja.pobierzId())) {
                            std::cout << " [UKONCZONA]";
                        }
                        std::cout << "\n";
                        for (const std::string& material : lekcja.pobierzMaterialy()) {
                            std::cout << "    Material: " << material << "\n";
                        }
                    }
                }
                break;
            }
            case 4: {
                const Kurs* kurs = wybierzKurs(kursant->pobierzKonto().pobierzAktywneKursy());
                if (kurs == nullptr) break;
                const Postep* postep = kursant->pobierzKonto().pobierzPostep(kurs->pobierzId());
                int idModulu = wybierzModul(*kurs, postep);
                if (idModulu == -1) break;
                for (const Modul& modul : kurs->pobierzModuly()) {
                    if (modul.pobierzId() == idModulu) {
                        int idLekcji = wybierzLekcje(modul, *postep);
                        if (idLekcji == -1) break;
                        if (platforma.ukonczLekcje(idKursanta, kurs->pobierzId(), idLekcji)) {
                            std::cout << "Ukonczono lekcje.\n";
                            if (postep->czyKursUkonczony()) {
                                std::cout << "Ukonczono kurs! Certyfikat jest dostepny.\n";
                            }
                        } else {
                            std::cout << "Nie mozna ukonczyc tej lekcji.\n";
                        }
                        break;
                    }
                }
                break;
            }
            case 5:
                wyswietlPostepy(*kursant, platforma);
                break;
            case 6: {
                std::cout << "\n=== MOJE CERTYFIKATY ===\n";
                std::vector<Certyfikat> certyfikaty =
                    kursant->pobierzKonto().pobierzCertyfikaty();
                if (certyfikaty.empty()) std::cout << "Brak certyfikatow.\n";
                for (const Certyfikat& certyfikat : certyfikaty) {
                    std::cout << "Certyfikat " << certyfikat.pobierzId()
                              << " - " << certyfikat.pobierzTytulKursu()
                              << ", data: " << certyfikat.pobierzDateWydania() << "\n";
                }
                break;
            }
            case 0:
                break;
            default:
                std::cout << "Nieprawidlowy wybor.\n";
        }
    }
}

int main() {
    PlatformaEdukacyjna platforma;

    // Przykladowi uzytkownicy
    platforma.dodajWykladowce(1, "Jan", "Kowalski", "W001", "2020-09-01", 6000);
    platforma.dodajWykladowce(2, "Anna", "Nowak", "W002", "2022-09-01", 5500);
    platforma.dodajKursanta(3, "Mikolaj", "Kortus");
    platforma.dodajKursanta(4, "Ktostam", "Jakistam");

    int wybor = -1;
    while (wybor != 0) {
        std::cout << "\n=== PLATFORMA EDUKACYJNA ===\n"
                  << "1. Panel wykladowcy\n"
                  << "2. Panel kursanta\n"
                  << "0. Wyjscie\nWybor: ";
        wybor = wczytajNumer();
        switch (wybor) {
            case 1:
                menuWykladowcy(platforma);
                break;
            case 2:
                menuKursanta(platforma);
                break;
            case 0:
                std::cout << "Koniec programu.\n";
                break;
            default:
                std::cout << "Nieprawidlowy wybor.\n";
        }
    }
    return 0;
}