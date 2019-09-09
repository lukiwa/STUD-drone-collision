#include "CuboidObstacle.hh"

/**
 * @brief Construct a new Cuboid Obstacle:: Cuboid Obstacle object
 *
 * @param middle_coords punkt srodkowy przeszkody
 * @param edge_length dlugosc boku przeszkody
 * @param height wysokosc przeszody
 * @param link lacze do gnuplota
 */
CuboidObstacle::CuboidObstacle(const Vector3D& middle_coords, double edge_length, double height,
                               PzG::GnuplotLink link, const Vector3D& orientation) {
    Init(middle_coords, edge_length, height, orientation);
    AddFilename(link);
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