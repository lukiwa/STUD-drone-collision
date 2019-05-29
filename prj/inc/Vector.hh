#pragma once

#include <assert.h>
#include <math.h>
#include <iostream>
#include "Counter.hh"
/**
 * @brief Szablon modeluje pojecie wektora
 *
 * @tparam Dimension ilosc wspolrzednych(skladowych) wektora
 */
template <int Dimension>
class Vector : public Counter<Vector<Dimension>> {
    double element[Dimension];

   public:
    using Counter<Vector<3>>::GetCounter;
    using Counter<Vector<3>>::GetCreated;
    static int curr_object_numb;
    static int max_object_numb;
    /* ------------------------------ KONSTRUKTORY ------------------------------ */
    Vector() {
        for (double &elem : element) elem = 0;
    }
    ~Vector() {}
    /**
     * @brief Construct a new Vector object
     *  NOTE Uzywa konstrukora klasy counter do zliczania obiektow
     * @param vector
     */
    Vector(const Vector<Dimension> &vector) : Counter<Vector<Dimension>>(vector) {
        for (int i = 0; i < Dimension; ++i) {
            element[i] = vector[i];
        }
    }

    /* ------------------ PRZECIAZENIA OPERATOROW INDEKSOWANIA ------------------ */

    /**
     * @brief Przeciazenie operatora indeksowania, sluzy do
     *        PRZYPISANIA odpowiednich wartosci skladowych wektora
     *
     * @param index numer indeksu
     * @return double& referencja do odpowiedniej skladowej wektora
     */
    inline double &operator[](unsigned int index) {
        assert(index >= 0 && index < Dimension);
        return element[index];
    }
    /**
     * @brief Przeciazenie operatora indeksowania, sluzy do
     *        POBRANIA WARTOSCI odpowiednich wartosci skladowych wektora
     *
     * @param index numer indeksu
     * @return double wartosc odpowiedniej skladowej wektora
     */

    inline double operator[](unsigned int index) const {
        assert(index >= 0 && index < Dimension);
        return element[index];
    }

    /* ---------------- PRZECIAZENIA OPERATOROW "ARYTMETYCZNYCH" ---------------- */
    /**
     * @brief Dodaje do siebie 2 wektory
     *
     * @param vector wektor do dodania
     * @return Vector<Dimension> wektor wynikowy o "Dimension" skladowych
     */
    inline Vector<Dimension> operator+(const Vector<Dimension> &vector) const {
        Vector<Dimension> result_vector;
        for (int i = 0; i < Dimension; ++i) {
            result_vector[i] = element[i] + vector[i];
        }
        return result_vector;
    }
    /**
     * @brief Mnozy wektor razy liczbe
     *
     * @param numb liczba rzeczywista
     * @return Vector<Dimension> wektor wynikowy o "Dimension" skladowych
     */
    inline Vector<Dimension> operator*(double numb) const {
        Vector<Dimension> result_vector;
        for (int i = 0; i < Dimension; ++i) {
            result_vector[i] = element[i] * numb;
        }
        return result_vector;
    }
    /**
     * @brief Odejmuje od siebie 2 wektory
     *
     * @param vector wektor do odjecia
     * @return Vector<Dimension> wektor wynikowy o "Dimension" skladowych
     */
    inline Vector<Dimension> operator-(const Vector<Dimension> &vector) const {
        Vector<Dimension> result_vector;
        for (int i = 0; i < Dimension; ++i) {
            result_vector[i] = element[i] + vector[i];
        }
        return result_vector;
    }
    /**
     * @brief Oblicza wektor przeciwny do danego
     *
     * @return Vector<Dimension> obloiczony wektor o "Dimension" skladowych bedacy przeciwnym.
     */
    inline Vector<Dimension> operator-(void) const {
        Vector<Dimension> result_vector;
        for (int i = 0; i < Dimension; ++i) {
            result_vector[i] = -element[i];
        }
        return result_vector;
    }

    /* --------------------------------- METODY --------------------------------- */

    static void DisplayObjectsNumb() {
        std::cout << std::endl;
        std::cout << "Laczna ilosc stworzonych obiektow klasy Wektor3D: ";
        std::cout << GetCreated();
        std::cout << std::endl;

        std::cout << "Ilosc istniejacych obiektow klasy Wektor3D: ";
        std::cout << GetCounter();
        std::cout << std::endl;
    }

    /**
     * @brief Oblicza nowy wektor w przestrzeni 3D
     *
     * Specializacja szablonu dla klasy wector dla wektora 3D
     *
     * @param vector Punkt koncowy na ktory wskazuje wektor
     * @return Vector3D Obliczony nowy wektor
     */
    Vector<Dimension> CalculateNewVector(const Vector<Dimension> &vector) const {
        Vector<Dimension> result_vector;
        for (int i = 0; i < Dimension; ++i) {
            result_vector[i] = vector[i] - (*this)[i];
        }
        return result_vector;
    }

    /**
     * @brief Oblicza dlugosc wektora w przestrzeni
     *
     * Specializacja szablonu dla klasy vector dla wektora3D
     *
     * @return double obliczona dlugosc wektora
     */
    double CalculateVectorLength(void) const {
        double result = 0;
        for (int i = 0; i < Dimension; ++i) {
            result += std::pow((*this)[i], 2);
        }
        result = std::sqrt(result);

        return result;
    }
};
// koniec klasy

/**
 * @brief Wczytuje wektor z danego strumienia
 *
 * @tparam Dimension Ilosc skladowych wektora
 * @param stream strumien wejsciowy
 * @param vector wektor, do ktorego maja zostac wczytane skladowe
 * @return std::ostream& referencja do uzytego strumienia
 */
template <int Dimension>
inline std::istream &operator>>(std::istream &stream, Vector<Dimension> &vector) {
    char readed;
    for (int i = 0; i < Dimension; ++i) {
        stream >> vector[i];

        stream.get(readed);
    }

    return stream;
}

/**
 * @brief Wyswietla wektor na dany strumien
 *
 * @tparam Dimension Ilosc skladowych wektora
 * @param stream strumien wyjsciowy
 * @param vector wektor, ktory ma zostac wysiwetlony
 * @return std::ostream& referencja do uzytego strumienia
 */
template <int Dimension>
inline std::ostream &operator<<(std::ostream &stream, const Vector<Dimension> &vector) {
    for (int i = 0; i < Dimension; ++i) {
        stream << vector[i] << " ";
    }
    return stream;
}
