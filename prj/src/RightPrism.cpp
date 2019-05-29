#include "RightPrism.hh"

/**
 * @brief Construct a new Right Prism:: Right Prism object
 *
 * @param vertex_vector wektor wierzcholkow graniastoslupa
 */
RightPrism::RightPrism(std::vector<Vector3D> vertex_vector) {
    vertex_coords = vertex_vector;
    org_vertex_coords = vertex_coords;
    vertex_numb = vertex_vector.size();
}

/**
 * @brief Wypisuje wierzcholki graniastoslupa pogrupowane po 4
 *
 * @param stream strumien na ktory maja byc wypisane wierzcholki
 * @return std::ostream& referencja do uzytego strumienia
 */
std::ostream &RightPrism::WriteVertexAs4(std::ostream &stream) const {
    for (unsigned int i = 0; i < vertex_numb; ++i) {
        stream << std::setw(16) << std::fixed << std::setprecision(10) << (*this)[i] << std::endl;
        if ((i + 1) % 4 == 0) stream << std::endl;  // robi przerwy co 4 linijki
    }

    // ponowny zapis pierwszego wierzcholka
    for (unsigned int i = 0; i < 4; ++i) {
        stream << std::setw(16) << std::fixed << std::setprecision(10) << (*this)[i] << std::endl;
        if ((i + 1) % 4 == 0) stream << std::endl;
    }

    return stream;
}
/**
 * @brief Wypelnia macierz rotacji odpowiednimi wartosciami
 *
 * @param rotation_angle wartosc kata obrotu wokol osi Z
 */
void RightPrism::FillZAxisMatrix(double rotation_angle) {
    rotation_matrix(0, 0) = std::cos(rotation_angle);
    rotation_matrix(0, 1) = -std::sin(rotation_angle);
    rotation_matrix(0, 2) = 0;
    rotation_matrix(1, 0) = std::sin(rotation_angle);
    rotation_matrix(1, 1) = std::cos(rotation_angle);
    rotation_matrix(1, 2) = 0;
    rotation_matrix(2, 0) = 0;
    rotation_matrix(2, 1) = 0;
    rotation_matrix(2, 2) = 1;
}

/**
 * @brief Wypelnia macierz rotacji odpowiednimi wartosciami
 *
 * @param rotation_angle wartosc kata obrotu wokol osi X
 */
void RightPrism::FillXAxisMatrix(double rotation_angle) {
    rotation_matrix(0, 0) = 1;
    rotation_matrix(0, 1) = 0;
    rotation_matrix(0, 2) = 0;
    rotation_matrix(1, 0) = 0;
    rotation_matrix(1, 1) = std::cos(rotation_angle);
    rotation_matrix(1, 2) = -std::sin(rotation_angle);
    rotation_matrix(2, 0) = 0;
    rotation_matrix(2, 1) = std::sin(rotation_angle);
    rotation_matrix(2, 2) = std::cos(rotation_angle);
}
/**
 * @brief Wypelnia macierz rotacji odpowiednimi wartosciami
 *
 * @param rotation_angle wartosc kata obrotu wokol osi Y
 */
void RightPrism::FillYAxisMatrix(double rotation_angle) {
    rotation_matrix(0, 0) = std::cos(rotation_angle);
    rotation_matrix(0, 1) = 0;
    rotation_matrix(0, 2) = std::sin(rotation_angle);
    rotation_matrix(1, 0) = 0;
    rotation_matrix(1, 1) = 1;
    rotation_matrix(1, 2) = 0;
    rotation_matrix(2, 0) = -std::sin(rotation_angle);
    rotation_matrix(2, 1) = 0;
    rotation_matrix(2, 2) = std::cos(rotation_angle);
}

/**
 * @brief Umozliwia rotacje danego graniastoslupa wokol osi
 *        Z o zadany kat
 *
 * @param rotation_angle kat rotacji wokol osi Z
 */
void RightPrism::RotateZAxis(double rotation_angle) {
    FillZAxisMatrix(rotation_angle);
    for (unsigned int i = 0; i < vertex_numb; ++i) {
        vertex_coords[i] = rotation_matrix * vertex_coords[i];
    }
}
/**
 * @brief Umozliwia rotacje danego graniastoslupa wokol osi
 *        Z o zadany kat
 *
 * @param rotation_angle kat rotacji wokol osi Z
 */
void RightPrism::RotateXAxis(double rotation_angle) {
    FillXAxisMatrix(rotation_angle);
    for (unsigned int i = 0; i < vertex_numb; ++i) {
        vertex_coords[i] = rotation_matrix * vertex_coords[i];
    }
}
/**
 * @brief Umozliwia rotacje danego graniastoslupa wokol osi
 *        Z o zadany kat
 *
 * @param rotation_angle kat rotacji wokol osi Z
 */
void RightPrism::RotateYAxis(double rotation_angle) {
    FillYAxisMatrix(rotation_angle);
    for (unsigned int i = 0; i < vertex_numb; ++i) {
        vertex_coords[i] = rotation_matrix * vertex_coords[i];
    }
}

/**
 * @brief Umozliwia przesuniecie o zadany wektor
 *
 * @param move_vector wektor przesuniecia
 */
void RightPrism::MoveByVector(const Vector3D &move_vector) {
    for (unsigned int i = 0; i < vertex_numb; ++i) {
        vertex_coords[i] = vertex_coords[i] + move_vector;
    }
}