#include "CuboidObstacle.hh"

CuboidObstacle::CuboidObstacle(const Vector3D& middle_coords, double edge_length, double height) {
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
}

/**
 * @brief Zapisuje wspolrzedne przeszkody do pliku
 *
 * @return true jezeli udalo sie zapisac
 * @return false jezeli nie udalo sie zapisac
 */
bool CuboidObstacle::WriteWertexToFile() {
    if (filename == "default") {
        std::cerr << "Nie dodano nazwy przeszkody prostopadloscianu!" << std::endl;
        return false;
    }

    std::ofstream file_stream;

    file_stream.open(filename);
    if (!file_stream.is_open()) {
        std::cerr << ":(  Operacja otwarcia do zapisu \"" << filename << "\"" << std::endl
                  << ":(  nie powiodla sie." << std::endl;
        return false;
    } else {
        WriteVertexAs4(file_stream);
        file_stream.close();
        return true;
    }
}
/**
 * @brief Detekcja kolizji drona z inna przeszkoda
 *
 * @param drone dron, dla ktorego wykrywana jest kolizja
 * @return true jezeli nastapila kolizja
 * @return false w przeciwnym wypadku
 */
bool CuboidObstacle::IsCollisionDetected(
    /*const Vector3D& drone_middle*/ std::shared_ptr<Drone> drone) const {
    contour.Init(this->vertex_coords, drone->GetEdgeLength(), drone->GetDroneHeight());
    Vector3D top_obstacle_coords;
    Vector3D bottom_obstacle_coords;

    contour.GetContourPoints(top_obstacle_coords, bottom_obstacle_coords);
    Vector3D drone_middle = drone->GetDroneMiddle();
    // dla x
    if (drone_middle[0] >= bottom_obstacle_coords[0] && drone_middle[0] <= top_obstacle_coords[0]) {
        // dla y
        if (drone_middle[1] >= bottom_obstacle_coords[1] &&
            drone_middle[1] <= top_obstacle_coords[1]) {
            // dla z
            if (drone_middle[2] >= bottom_obstacle_coords[2] &&
                drone_middle[2] <= top_obstacle_coords[2]) {
                return true;
            }
        }
    }
    return false;
}