#pragma once

#include <string>
#include <vector>
#include <memory>
#include "Kursant.h"
#include "Wykladowca.h"
#include "Kurs.h"

class PlatformaEdukacyjna {
private:
    std::vector<std::unique_ptr<Kursant>> listaKursantow;
    std::vector<std::unique_ptr<Wykladowca>> listaWykladowcow;
    std::vector<std::unique_ptr<Kurs>> katalogKursow;
    int nastepneIdKursu;
    int nastepneIdModulu;
    int nastepneIdLekcji;
    int nastepneIdCertyfikatu;

    // Metody pomocnicze
    Kurs* znajdzKurs(int idKursu) const;
    Kursant* znajdzKursanta(int idKursanta) const;
    bool czyWykladowcaIstnieje(std::string idPracownika) const;
    bool czyKursMaZapisy(int idKursu) const;

public:
    // Konstruktor
    PlatformaEdukacyjna();

    // Dodawanie uzytkownikow
    bool dodajKursanta(int id, std::string imie, std::string nazwisko);
    bool dodajWykladowce(int id, std::string imie, std::string nazwisko,
                         std::string idPracownika,
                         std::string dataZatrudnienia, double pensja);

    // Zarzadzanie kursami
    bool dodajKurs(std::string idPracownika, Kurs kurs);
    bool usunKurs(std::string idPracownika, int idKursu);
    bool dodajModul(std::string idPracownika, int idKursu, Modul modul);
    bool dodajLekcje(std::string idPracownika, int idKursu,
                     int idModulu, Lekcja lekcja);

    // Automatyczne identyfikatory
    int utworzKurs(std::string idPracownika, std::string tytul);
    int utworzModul(std::string idPracownika, int idKursu, std::string tytul);
    int utworzLekcje(std::string idPracownika, int idKursu,
                     int idModulu, std::string tytul, std::string material);

    // Zapisy i postepy
    bool zapiszNaKurs(int idKursanta, int idKursu);
    bool ukonczLekcje(int idKursanta, int idKursu, int idLekcji);

    // Statystyki
    std::vector<Postep> pobierzStatystykiKursu(
        std::string idPracownika, int idKursu) const;
    std::vector<Postep> pobierzStatystykiKursanta(
        std::string idPracownika, int idKursanta) const;

    // Gettery
    const Kursant* pobierzKursanta(int idKursanta) const;
    const Kurs* pobierzKurs(int idKursu) const;
    std::vector<const Kurs*> pobierzKursy() const;
    std::vector<const Kursant*> pobierzKursantow() const;
    std::vector<const Wykladowca*> pobierzWykladowcow() const;
};