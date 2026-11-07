#pragma once

#include <string>
#include <vector>

class Lekcja {
private:
    int idLekcji;
    std::string tytul;
    std::vector<std::string> materialy;

public:
    // Konstruktor
    Lekcja(int id, std::string tytul);

    // Gettery
    int pobierzId() const;
    std::string pobierzTytul() const;

    // Metody
    void dodajMaterial(std::string material);
    bool usunMaterial(std::string material);
    std::vector<std::string> pobierzMaterialy() const;
};