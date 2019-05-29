#include "Cuboid.hh"

/**
 * @brief Umozliwia rotacje danego prostopadloscoanu
 *
 * @param Zrotation_angle z skladowa rotacji
 * @param Xrotation_angle x skladowa rotacji
 * @param Yrotation_angle y skladowa rotacji
 */
void Cuboid::Rotate(double Zrotation_angle, double Xrotation_angle, double Yrotation_angle) {
    Vector3D to_fix_corpus_postion[2];

    to_fix_corpus_postion[0] = vertex_coords[0];

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

    to_fix_corpus_postion[1] = vertex_coords[0];

    // Po rotacji prostopadloscianu wokol osi OZ przesuwany jest o wektor, bedacy
    // roznica miedzy starym wierzcholkiem a nowym wierzcholkiem

    Vector3D corpus_fix_move_vector =
        to_fix_corpus_postion[1].CalculateNewVector(to_fix_corpus_postion[0]);

    MoveByVector(corpus_fix_move_vector);
}

/**
 * @brief Inizializacja prostopadloscianu o danych wymiarach
 *
 * @param middle_coords punkt srodkowy prostopadloscianu
 * @param edge_length dlugosc boku
 * @param height wysokosc
 * @param orientation poczatkowa orietnacja, gdzie skladowe wektora to odpowiednio:
 *                    0 -x, 1 -y, 2-z
 */
void Cuboid::Init(const Vector3D& middle_coords, double edge_length, double height,
                  Vector3D orientation) {
    build_point = middle_coords;
    std::vector<Vector3D> coords;                // wspolrzedne wierzcholkow
    Vector3D top_middle_coords = middle_coords;  // gorny punkt na srodku prostpadloscianu
    // Rozpoczynam wpisywanie od gornego srodkowego punktu
    top_middle_coords[2] = middle_coords[2] + height / 2;

    /* -------------------------------------------------------------------------- */
    coords.push_back(top_middle_coords);

    coords.push_back(Insert(top_middle_coords[0] - edge_length / 2,
                            top_middle_coords[1] + edge_length / 2, top_middle_coords[2]));

    coords.push_back(Insert(top_middle_coords[0] - edge_length / 2,
                            top_middle_coords[1] + edge_length / 2, top_middle_coords[2] - height));

    coords.push_back(
        Insert(top_middle_coords[0], top_middle_coords[1], top_middle_coords[2] - height));

    /* -------------------------------------------------------------------------- */
    coords.push_back(top_middle_coords);
    coords.push_back(Insert(top_middle_coords[0] + edge_length / 2,
                            top_middle_coords[1] + edge_length / 2, top_middle_coords[2]));

    coords.push_back(Insert(top_middle_coords[0] + edge_length / 2,
                            top_middle_coords[1] + edge_length / 2, top_middle_coords[2] - height));

    coords.push_back(
        Insert(top_middle_coords[0], top_middle_coords[1], top_middle_coords[2] - height));

    /* -------------------------------------------------------------------------- */
    coords.push_back(top_middle_coords);
    coords.push_back(Insert(top_middle_coords[0] + edge_length / 2,
                            top_middle_coords[1] - edge_length / 2, top_middle_coords[2]));

    coords.push_back(Insert(top_middle_coords[0] + edge_length / 2,
                            top_middle_coords[1] - edge_length / 2, top_middle_coords[2] - height));

    coords.push_back(
        Insert(top_middle_coords[0], top_middle_coords[1], top_middle_coords[2] - height));
    /* -------------------------------------------------------------------------- */
    coords.push_back(top_middle_coords);
    coords.push_back(Insert(top_middle_coords[0] - edge_length / 2,
                            top_middle_coords[1] - edge_length / 2, top_middle_coords[2]));

    coords.push_back(Insert(top_middle_coords[0] - edge_length / 2,
                            top_middle_coords[1] - edge_length / 2, top_middle_coords[2] - height));

    coords.push_back(
        Insert(top_middle_coords[0], top_middle_coords[1], top_middle_coords[2] - height));

    this->vertex_coords = coords;
    this->vertex_numb = coords.size();
    this->edge_length = edge_length;
    this->height = height;

    /* ------------- ZMIANA POCZTKOWEJ ORIENTACJI PROSTOPADLOSCIANU ------------- */
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