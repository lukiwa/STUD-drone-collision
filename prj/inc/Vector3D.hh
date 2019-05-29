#pragma once

#include <math.h>
#include "Vector.hh"

#define THIS_VECTOR_SIZE 3

/**
 * @brief Instancja szablonu wektor dla wektora o 3 skladowych
 *
 */
typedef Vector<THIS_VECTOR_SIZE> Vector3D;

Vector3D Insert(double x, double y, double z);
