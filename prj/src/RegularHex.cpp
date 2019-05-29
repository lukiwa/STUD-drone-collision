#include "RegularHex.hh"

/**
 * @brief Inicializacja rotora
 *
 * @param mounting_point punkt mocowania rotora do korpusu
 * @param rotor_edge_length dlugosc boku rotora
 * @param rotor_height wyskosc rotora
 */
void RegularHex::Init(const Vector3D& mounting_point, double rotor_edge_length, double rotor_height,
                      Vector3D orientation) {
    build_point = mounting_point;
    std::vector<Vector3D> coords;      // wspolrzedne wierzcholkow
    Vector3D rotor_top_middle_coords;  // gorny srodkowy punkt rotora
    double triangle_height =
        (rotor_edge_length * std::sqrt(3)) / 2;  // wysokosc trojkata(boku rotora)

    rotor_top_middle_coords = mounting_point + Insert(0, 0, rotor_height);

    /* -------------------------------------------------------------------------- */
    coords.push_back(rotor_top_middle_coords);
    coords.push_back(Insert(rotor_top_middle_coords[0] - rotor_edge_length,
                            rotor_top_middle_coords[1], rotor_top_middle_coords[2]));

    coords.push_back(Insert(rotor_top_middle_coords[0] - rotor_edge_length,
                            rotor_top_middle_coords[1], rotor_top_middle_coords[2] - rotor_height));

    coords.push_back(Insert(rotor_top_middle_coords[0], rotor_top_middle_coords[1],
                            rotor_top_middle_coords[2] - rotor_height));

    /* -------------------------------------------------------------------------- */
    coords.push_back(rotor_top_middle_coords);
    coords.push_back(Insert(rotor_top_middle_coords[0] - rotor_edge_length / 2,
                            rotor_top_middle_coords[1] + triangle_height,
                            rotor_top_middle_coords[2]));

    coords.push_back(Insert(rotor_top_middle_coords[0] - rotor_edge_length / 2,
                            rotor_top_middle_coords[1] + triangle_height,
                            rotor_top_middle_coords[2] - rotor_height));

    coords.push_back(Insert(rotor_top_middle_coords[0], rotor_top_middle_coords[1],
                            rotor_top_middle_coords[2] - rotor_height));

    /* -------------------------------------------------------------------------- */
    coords.push_back(rotor_top_middle_coords);
    coords.push_back(Insert(rotor_top_middle_coords[0] + rotor_edge_length / 2,
                            rotor_top_middle_coords[1] + triangle_height,
                            rotor_top_middle_coords[2]));

    coords.push_back(Insert(rotor_top_middle_coords[0] + rotor_edge_length / 2,
                            rotor_top_middle_coords[1] + triangle_height,
                            rotor_top_middle_coords[2] - rotor_height));

    coords.push_back(Insert(rotor_top_middle_coords[0], rotor_top_middle_coords[1],
                            rotor_top_middle_coords[2] - rotor_height));

    /* -------------------------------------------------------------------------- */
    coords.push_back(rotor_top_middle_coords);
    coords.push_back(Insert(rotor_top_middle_coords[0] + rotor_edge_length,
                            rotor_top_middle_coords[1], rotor_top_middle_coords[2]));

    coords.push_back(Insert(rotor_top_middle_coords[0] + rotor_edge_length,
                            rotor_top_middle_coords[1], rotor_top_middle_coords[2] - rotor_height));

    coords.push_back(Insert(rotor_top_middle_coords[0], rotor_top_middle_coords[1],
                            rotor_top_middle_coords[2] - rotor_height));
    /* -------------------------------------------------------------------------- */
    coords.push_back(rotor_top_middle_coords);
    coords.push_back(Insert(rotor_top_middle_coords[0] + rotor_edge_length / 2,
                            rotor_top_middle_coords[1] - triangle_height,
                            rotor_top_middle_coords[2]));

    coords.push_back(Insert(rotor_top_middle_coords[0] + rotor_edge_length / 2,
                            rotor_top_middle_coords[1] - triangle_height,
                            rotor_top_middle_coords[2] - rotor_height));

    coords.push_back(Insert(rotor_top_middle_coords[0], rotor_top_middle_coords[1],
                            rotor_top_middle_coords[2] - rotor_height));
    /* -------------------------------------------------------------------------- */
    coords.push_back(rotor_top_middle_coords);
    coords.push_back(Insert(rotor_top_middle_coords[0] - rotor_edge_length / 2,
                            rotor_top_middle_coords[1] - triangle_height,
                            rotor_top_middle_coords[2]));

    coords.push_back(Insert(rotor_top_middle_coords[0] - rotor_edge_length / 2,
                            rotor_top_middle_coords[1] - triangle_height,
                            rotor_top_middle_coords[2] - rotor_height));

    coords.push_back(Insert(rotor_top_middle_coords[0], rotor_top_middle_coords[1],
                            rotor_top_middle_coords[2] - rotor_height));
    this->vertex_coords = coords;
    this->vertex_numb = coords.size();

    /* -------------ZMIANA POCZTKOWEJ ORIENTACJI SZESCIOKATNEGO------------- */
    if (orientation[0] != 0) {
        Rotate(0, orientation[0], 0);
    }
    if (orientation[1] != 0) {
        Rotate(0, 0, orientation[0]);
    }
    if (orientation[2] != 0) {
        Rotate(orientation[2], 0, 0);
    }
}

/**
 * @brief Umozliwia rotacje szesciokatnego
 *
 * @param Zrotation_angle z skladowa rotacji
 * @param Xrotation_angle x skladowa rotacji
 * @param Yrotation_angle y skladowa rotacji
 */
void RegularHex::Rotate(double Zrotation_angle, double Xrotation_angle, double Yrotation_angle) {
    Vector3D points_to_fix[2];
    points_to_fix[0] = build_point;

    /* ----------------------- Rotacja wokol wybranej osi ----------------------- */
    if (Zrotation_angle != 0) {
        RotateZAxis(Zrotation_angle);
    }
    if (Xrotation_angle != 0) {
        RotateXAxis(Xrotation_angle);
    }
    if (Yrotation_angle != 0) {
        RotateYAxis(Yrotation_angle);
    }

    points_to_fix[1] =
        vertex_coords[3];  // dolny srodkowy punkt ma byc przeusniety do punktu mocowania
    Vector3D fix_vector = points_to_fix[1].CalculateNewVector(points_to_fix[0]);
    MoveByVector(fix_vector);
}