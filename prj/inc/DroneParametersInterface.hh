#pragma once
#include <memory>
#include "Drone.hh"
#include "SceneObject.hh"
#include "Vector3D.hh"

struct DroneParameters {
    double height;
    double edge_length;
    double rotor_edge_length;
    double rotor_height;
    Vector3D corpus_middle_coords;
};

class DroneCreationInterface {
   public:
    DroneCreationInterface() = default;
    virtual ~DroneCreationInterface() = default;

    virtual std::shared_ptr<Drone> CreateDrone() = 0;
    virtual void SetDroneParam(double height, double edge_length, double rotor_edge_length,
                               double rotor_height, const Vector3D& corpus_middle_coords) = 0;
    virtual void DeleteDrone(std::shared_ptr<Drone>) = 0;
};
