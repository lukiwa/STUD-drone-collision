#include "Vector3D.hh"

/**
 * @brief Sluzy do wstawienia wspolrzednych wektora 3 wymiarowego
 *
 * @param odpowiednie wspolrzedne
 * @return Vector3D utworzony wektor o danych wspolrzednych
 */
Vector3D Insert(double x, double y, double z) {
    Vector3D result_vector;
    result_vector[0] = x;
    result_vector[1] = y;
    result_vector[2] = z;
    return result_vector;
}