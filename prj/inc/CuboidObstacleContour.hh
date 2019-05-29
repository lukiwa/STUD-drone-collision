#pragma once
#include "Vector3D.hh"
#include "vector"

/**
 * @brief Definiuje pojecie obrysu przeszkody w postaci 2 wektorow
 *  polozonych skrajnie w stosunku do przeszkody
 *
 */
class CuboidObstacleContour {
   private:
   protected:
    Vector3D top_coords;     // skrajne gorne polzenie
    Vector3D bottom_coords;  // skrajne dolne polozenie

   public:
    CuboidObstacleContour() {}
    ~CuboidObstacleContour() {}

    /**
     * @brief Inizialicia obrysu przeszkody na podstawie podanych wymiarow
     *
     * @param obstacle_coords wspolrzedne przeszkody dla ktorej ma byc wykonany obrys
     * @param config_height wysokosc obrysu
     * @param config_edge_length dlugosc i szerokosc obrysu
     */
    void Init(const std::vector<Vector3D>& obstacle_coords, double config_height,
              double config_edge_length) {
        this->top_coords = Insert(obstacle_coords[5][0] + config_edge_length / 2,
                                  obstacle_coords[5][1] + config_edge_length / 2,
                                  obstacle_coords[5][2] + config_height / 2);

        this->bottom_coords = Insert(obstacle_coords[14][0] - config_edge_length / 2,
                                     obstacle_coords[14][1] - config_edge_length / 2,
                                     obstacle_coords[14][2] - config_height / 2);
    }
    /**
     * @brief Dostep do punktow skrajnych obrysu
     *
     * @param out_top_coords gorny skrajny punkt
     * @param out_bottom_coords dolny skrajny punkt
     */
    void GetContourPoints(Vector3D& out_top_coords, Vector3D& out_bottom_coords) const {
        out_top_coords = this->top_coords;
        out_bottom_coords = this->bottom_coords;
    }
};
