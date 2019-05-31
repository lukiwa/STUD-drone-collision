#pragma once
#include <memory>
#include "Drone.hh"
#include "DroneParametersInterface.hh"
#include "SceneObject.hh"

/**
 * @brief Singleton fabryki obiektow, umozliwa tworzenie
 *        odpowiednio zainicializowanych obiektow sceny
 */
class ObjectFactory : public Drone {
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
    /*
        std::shared_ptr<SceneObject> CreateDrone() override {
            return std::make_shared<Drone>(height, edge_length, rotor_edge_length, rotor_height,
                                           corpus_middle_coords);
        }
        */
};
