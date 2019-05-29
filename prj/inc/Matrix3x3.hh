#pragma once

#include <iostream>
#include "Vector3D.hh"

#include "Matrix.hh"

#define THIS_MATRIX_SIZE 3

/**
 * @brief Instancja szablonu matrix- modeluje pojecie macierzy 3x3.
 *        Umozliwia mnozenie przez siebie dwoch macierzy, oraz mnozenia
 *        macierzy przez wektor
 *
 */
typedef Matrix<THIS_MATRIX_SIZE> Matrix3x3;
