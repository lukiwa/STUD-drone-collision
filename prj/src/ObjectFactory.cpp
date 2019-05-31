#include "ObjectFactory.hh"

int ObjectFactory::created_drone_numb = 0;
int ObjectFactory::created_obstacle_numb = 0;

void ObjectFactory::SetDroneParam(double height, double edge_length, double rotor_edge_length, double rotor_height,
                                  const Vector3D& corpus_middle_coords) {
    DroneParameters::height = height;
    DroneParameters::edge_length = edge_length;
    DroneParameters::rotor_edge_length = rotor_edge_length;
    DroneParameters::rotor_height = rotor_height;
    DroneParameters::corpus_middle_coords = corpus_middle_coords;
}

std::shared_ptr<Drone> ObjectFactory::CreateDrone(PzG::GnuplotLink& link) {
    ++created_drone_numb;
    return std::make_shared<Drone>(DroneParameters::height, DroneParameters::edge_length,
                                   DroneParameters::rotor_edge_length, DroneParameters::rotor_height,
                                   DroneParameters::corpus_middle_coords);
}

void ObjectFactory::DeleteDrone(std::shared_ptr<Drone> drone) {
    // TODO
}

void ObjectFactory::SetDroneFilename(std::shared_ptr<Drone> drone, PzG::GnuplotLink& link) {
    drone->AddMembersFilenames(link, created_drone_numb);
}

/* -------------------------------------------------------------------------- */

std::shared_ptr<CuboidObstacle> ObjectFactory::CreateObstacle() {
    ++created_obstacle_numb;
    return std::make_shared<CuboidObstacle>(ObstacleParameters::middle_coords, ObstacleParameters::edge_length,
                                            ObstacleParameters::height);
}
void ObjectFactory::SetObstacleParam(double height, double edge_length, const Vector3D& middle_coords) {
    ObstacleParameters::height = height;
    ObstacleParameters::edge_length = edge_length;
    ObstacleParameters::middle_coords = middle_coords;
}
// TODO
void ObjectFactory::DeleteObstacle(std::shared_ptr<Drone> drone) {}
void ObjectFactory::SetObstacleFilename(std::shared_ptr<CuboidObstacle> obstacle, PzG::GnuplotLink& link) {
    obstacle->AddFilename(link);
}