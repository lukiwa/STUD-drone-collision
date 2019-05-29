#pragma once

#include <assert.h>
#include <iostream>
#include "Vector.hh"

/**
 * @brief Szablon modeluje pojecie macierzy kwadratowej
 *
 * @tparam Dimension wymiar macierzy
 */
template <int Dimension>
class Matrix {
    Vector<Dimension> element[Dimension];

   public:
    Matrix();
    ~Matrix() {}

    /**
     * @brief Pozwala na dostep do wartosci obiektu macierz
     *
     * @param row dany wiersz
     * @param col dana kolumna
     * @return double to co jest przechowywane w danym wierszu i kolumnie
     */
    inline double operator()(unsigned int row, unsigned int col) const {
        assert(row >= 0 && row < Dimension);
        assert(col >= 0 && col < Dimension);
        return element[row][col];
    }

    /**
     * @brief Pozwala na modyfikowanie do wartosci obiektu macierz
     *
     * @param row dany wiersz
     * @param col dana kolumna
     * @return double to co jest aktualnie przechowywane w danym wierszu i kolumnie
     */
    inline double &operator()(unsigned int row, unsigned int col) {
        assert(row >= 0 && row < Dimension);
        assert(col >= 0 && col < Dimension);
        return element[row][col];
    }

    /**
     * @brief Umozliwia mnozenie przez siebie macierzy 3x3
     *
     * Obietk z ktorego wywolamy mnozenie jest druga macierza tj:
     * MacierzParam * MacierzWywolana
     *
     * @param matrix macierz, ktora bedzie mnozona przez wywloana macierz
     * @return Matrix3x3 rezultat mnozenia
     */
    Matrix<Dimension> operator*(const Matrix<Dimension> &matrix) const {
        Matrix<Dimension> result_matrix;
        for (int i = 0; i < Dimension; i++)
            for (int j = 0; j < Dimension; j++) {
                for (int u = 0; u < Dimension; u++)
                    result_matrix(i, j) += (*this)(i, u) * matrix(u, j);
            }

        return result_matrix;
    }

    /**
     * @brief Umozliwia mnozenie macierzy przez wektor
     *
     * @param vector wektor przez ktory zostanie pomnozona macierz
     * @return Vector3D wektor wynikowy
     */
    Vector<Dimension> operator*(const Vector<Dimension> &vector) const {
        Vector<Dimension> result_vector;
        for (int i = 0; i < Dimension; ++i) {
            for (int j = 0; j < Dimension; ++j) {
                result_vector[i] += (*this)(i, j) * vector[j];
            }
        }
        return result_vector;
    }

    /* ------------------------------ ROZSZERZENIE ------------------------------ */
    inline Matrix<Dimension> operator+(const Matrix<Dimension> &matrix) const {
        Matrix<Dimension> result_matrix;
        for (int i = 0; i < Dimension; i++)
            for (int j = 0; j < Dimension; j++) {
                result_matrix(i, i) = (*this)(i, j) + matrix(i, j);
            }
        return result_matrix;
    }

    inline Matrix<Dimension> operator-(const Matrix<Dimension> &matrix) const {
        Matrix<Dimension> result_matrix;
        for (int i = 0; i < Dimension; i++)
            for (int j = 0; j < Dimension; j++) {
                result_matrix(i, j) = (*this)(i, j) - matrix(i, j);
            }
        return result_matrix;
    }

    inline bool operator==(const int zero) const {
        assert(zero == 0);
        double temp;
        for (int i = 0; i < Dimension; ++i) {
            for (int j = 0; j < Dimension; ++j) {
                temp += (*this)(i, j);
            }
        }
        if (temp == zero)
            return true;
        else
            return false;
    }
};

/**
 * @brief Construct a new Matrix< Dimension>:: Matrix object
 *
 * @tparam Dimension rozmiar macierzy
 */
template <int Dimension>
Matrix<Dimension>::Matrix() {
    for (int i = 0; i < Dimension; ++i) {
        for (int j = 0; j < Dimension; ++j) {
            element[i][j] = 0;
        }
    }
}

/**
 * @brief Wypisuje zawartosc macierzy kwadratowej na zadany strumien
 *
 * @tparam Dimension rozmiar macierzy
 * @param stream wybrany strumien
 * @param matrix wybrana macierz
 * @return std::ostream& referencja do uzytego strumienia
 */
template <int Dimension>
inline std::ostream &operator<<(std::ostream &stream, const Matrix<Dimension> &matrix) {
    for (int i = 0; i < Dimension; ++i) {
        for (int j = 0; j < Dimension; j++) {
            stream << matrix(i, j) << " ";
        }
        stream << std::endl;
    }

    return stream;
}
