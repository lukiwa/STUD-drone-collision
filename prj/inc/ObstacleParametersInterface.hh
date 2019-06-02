#pragma once
#include <memory>
#include "CuboidObstacle.hh"
#include "SceneObject.hh"
#include "Vector3D.hh"

/**
 * @brief Interfejs sluzacy do tworzenia przeszkod na scenie
 *
 */
class ObstacleCreationInterface {
   public:
    ObstacleCreationInterface() = default;
    virtual ~ObstacleCreationInterface() = default;

    /**
     * @brief Tworzy przeszkodze na podstawie wczesniej zdefiniowanych parametrow
     *
     * @return std::shared_ptr<CuboidObstacle>
     */
    virtual std::shared_ptr<CuboidObstacle> CreateObstacle() = 0;
    /**
     * @brief Ustawia parametry przeszkody
     *
     * @param height wysokosc przeszkody
     * @param edge_length dlugosc boku podstawy
     * @param middle_coords punkt srodkowy
     */
    virtual void SetObstacleParam(double height, double edge_length, const Vector3D& middle_coords) = 0;

    /** FIXME
     * @brief Usuwa zadana przeszkdoe
     *
     * @param wskaznik do przeszkody ktora ma byc usunieta
     */
    virtual void DeleteObstacle(std::shared_ptr<CuboidObstacle> obstacle) = 0;

    /**
     * @brief Ustawia nazwe pliku do zapisu przeszkody i dodaje ta nazwe do lacza do gnuplota
     *
     * @param obstacle wskaznik na przeszkode
     * @param link lacze do gnuplota
     */
    virtual void SetObstacleFilename(std::shared_ptr<CuboidObstacle> obstacle, PzG::GnuplotLink& link) = 0;
};

/**
 * @brief Struktura zawierajaca parametry przeszkody
 *
 */
struct ObstacleParameters : public ObstacleCreationInterface {
    Vector3D middle_coords;
    double edge_length;
    double height;
};
