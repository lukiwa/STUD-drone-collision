#pragma once
#include <memory>
#include "Drone.hh"
#include "DroneParametersInterface.hh"
#include "SceneObject.hh"

/**
 * @brief Singleton fabryki obiektow, umozliwa tworzenie
 *        odpowiednio zainicializowanych obiektow sceny
 */
class ObjectFactory : public DroneParameters {
    static int created_drone_numb;

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

    std::shared_ptr<Drone> CreateDrone(PzG::GnuplotLink& link) override;
    void SetDroneParam(double height, double edge_length, double rotor_edge_length,
                       double rotor_height, const Vector3D& corpus_middle_coords) override;
    // TODO
    void DeleteDrone(std::shared_ptr<Drone> drone) override;
    void SetDroneFilename(std::shared_ptr<Drone> drone, PzG::GnuplotLink& link) override;
};
