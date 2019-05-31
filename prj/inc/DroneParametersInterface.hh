#pragma once
#include <memory>
#include "Drone.hh"
#include "SceneObject.hh"
#include "Vector3D.hh"

class DroneCreationInterface {
   public:
    DroneCreationInterface() = default;
    virtual ~DroneCreationInterface() = default;

    virtual std::shared_ptr<Drone> CreateDrone(PzG::GnuplotLink& link) = 0;
    virtual void SetDroneParam(double height, double edge_length, double rotor_edge_length,
                               double rotor_height, const Vector3D& corpus_middle_coords) = 0;
    virtual void DeleteDrone(std::shared_ptr<Drone> drone) = 0;
    virtual void SetDroneFilename(std::shared_ptr<Drone> drone, PzG::GnuplotLink& link) = 0;
};

struct DroneParameters : public DroneCreationInterface {
    double height = 10;
    double edge_length = 10;
    double rotor_edge_length = 5;
    double rotor_height = 5;
     Vector3D corpus_middle_coords = Insert(25, 25, 25);
};
