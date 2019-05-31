#pragma once
#include <memory>
#include "Drone.hh"
#include "DroneParametersInterface.hh"
#include "ObstacleParametersInterface.hh"
#include "SceneObject.hh"

/**
 * @brief Singleton fabryki obiektow, umozliwa tworzenie
 *        odpowiednio zainicializowanych obiektow sceny
 */
class ObjectFactory : public DroneParameters, public ObstacleParameters {
    static int created_drone_numb;
    static int created_obstacle_numb;

   private:
    ObjectFactory() = default;
    ObjectFactory(const ObjectFactory&) = delete;
    ObjectFactory& operator=(const ObjectFactory&) = delete;

   public:
    ~ObjectFactory() = default;
    /**
     * @brief Dostep do singletonu fabryki obiektow
     *
     *
     * @return ObjectFactory* wskaznik na instancje fabryki obiektow
     */
    static ObjectFactory* Get() {
        static ObjectFactory instance;
        return &instance;
    }

    /* -------------------------------- DLA DRONA ------------------------------- */
    std::shared_ptr<Drone> CreateDrone(PzG::GnuplotLink& link) override;
    void SetDroneParam(double height, double edge_length, double rotor_edge_length, double rotor_height,
                       const Vector3D& corpus_middle_coords) override;
    // TODO
    void DeleteDrone(std::shared_ptr<Drone> drone) override;
    void SetDroneFilename(std::shared_ptr<Drone> drone, PzG::GnuplotLink& link) override;
    /* ----------------------------- DLA PRZESZKODY ----------------------------- */

    std::shared_ptr<CuboidObstacle> CreateObstacle() override;
    void SetObstacleParam(double height, double edge_length, const Vector3D& middle_coords) override;
    void DeleteObstacle(std::shared_ptr<Drone> drone) override;
    void SetObstacleFilename(std::shared_ptr<CuboidObstacle> obstacle, PzG::GnuplotLink& link) override;
};
