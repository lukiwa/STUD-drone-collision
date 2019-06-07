#pragma once
#include <memory>
#include "Drone.hh"
#include "SceneObject.hh"
#include "Vector3D.hh"

/**
 * @brief Interfejs sluzacy do tworzenia obiektu drona na scenie
 *
 */
class DroneCreationInterface {
   public:
    DroneCreationInterface() = default;
    virtual ~DroneCreationInterface() = default;

    /**
     * @brief Tworzeni obiektu drona na podstawie zadanych wczesniej parametrow
     *
     * @return std::shared_ptr<Drone>
     */
    virtual std::shared_ptr<Drone> CreateDrone() = 0;

    /**
     * @brief Ustawia parametry drona
     *
     * @param height wysokosc korpusu
     * @param edge_length dlugosc krawedzi korpusu
     * @param rotor_edge_length dlugosc krawedzi rotora
     * @param rotor_height wysokosc rotora
     * @param corpus_middle_coords punkt srodkowy drona(korpusu)
     */
    virtual void SetDroneParam(double height, double edge_length, double rotor_edge_length, double rotor_height,
                               const Vector3D& corpus_middle_coords) = 0;

    /** FIXME
     * @brief Usuwa drona
     *
     * @param drone wskaznik na dron do usuniecia
     */
    virtual void DeleteDrone(std::shared_ptr<Drone> drone) = 0;

    /**
     * @brief Ustala srodek drona nie modyfikujac jego wymiarow
     *
     * @param corpus_middle_coords wspolrzedne srodka
     */
    virtual void SetDroneMiddle(const Vector3D& corpus_middle_coords) = 0;
};

/**
 * @brief Struktura zawierajaca parametry drona
 *
 */
struct DroneParameters : public DroneCreationInterface {
    double height = 10;
    double edge_length = 10;
    double rotor_edge_length = 5;
    double rotor_height = 5;
    Vector3D corpus_middle_coords = Insert(25, 25, 25);
};
