#include "ObjectFactory.hh"

int ObjectFactory::created_drone_numb = 0;
int ObjectFactory::created_obstacle_numb = 0;

/**
 * @brief Dostep do instancji fabryki obiektow
 *
 * @return ObjectFactory* wskaznik na instancje fabryki obiektow
 */
ObjectFactory* ObjectFactory::Get() {
    static ObjectFactory instance;
    return &instance;
}

/**
 * @brief  Ustawia parametry drona(patrz klase DroneCreationInterface )
 *
 */
void ObjectFactory::SetDroneParam(double height, double edge_length, double rotor_edge_length, double rotor_height,
                                  const Vector3D& corpus_middle_coords) {
    DroneParameters::height = height;
    DroneParameters::edge_length = edge_length;
    DroneParameters::rotor_edge_length = rotor_edge_length;
    DroneParameters::rotor_height = rotor_height;
    DroneParameters::corpus_middle_coords = corpus_middle_coords;
}

/**
 * @brief Tworzy obiekt drona(patrz klase DroneCreationInterface )
 *
 */
std::shared_ptr<Drone> ObjectFactory::CreateDrone() {
    ++created_drone_numb;
    return std::make_shared<Drone>(DroneParameters::height, DroneParameters::edge_length,
                                   DroneParameters::rotor_edge_length, DroneParameters::rotor_height,
                                   DroneParameters::corpus_middle_coords);
}

/**FIXME
 * @brief Usuwa drona(patrz klase DroneCreationInterface )
 *
 */
void ObjectFactory::DeleteDrone(std::shared_ptr<Drone> drone) {}

/**
 * @brief Ustawia nazwe drona (patrz klase DroneCreationInterface )
 *
 */
void ObjectFactory::SetDroneFilename(std::shared_ptr<Drone> drone, PzG::GnuplotLink& link) {
    drone->AddMembersFilenames(link, created_drone_numb);
}

/* -------------------------------------------------------------------------- */
/**
 * @brief Tworzy przeszkode(patrz klase ObstacleCreationInterface )
 *
 */
std::shared_ptr<CuboidObstacle> ObjectFactory::CreateObstacle() {
    ++created_obstacle_numb;
    return std::make_shared<CuboidObstacle>(ObstacleParameters::middle_coords, ObstacleParameters::edge_length,
                                            ObstacleParameters::height);
}

/**
 * @brief Ustawia parametry przeszkody(patrz klase ObstacleCreationInterface )
 *
 */
void ObjectFactory::SetObstacleParam(double height, double edge_length, const Vector3D& middle_coords) {
    ObstacleParameters::height = height;
    ObstacleParameters::edge_length = edge_length;
    ObstacleParameters::middle_coords = middle_coords;
}
/**FIXME
 * @brief Usuwa przeszkode(patrz klase ObstacleCreationInterface )
 *
 */
void ObjectFactory::DeleteObstacle(std::shared_ptr<CuboidObstacle> obstacle) {}

/**
 * @brief Ustawia nazwe przeszkody(patrz klase ObstacleCreationInterface )
 *
 */
void ObjectFactory::SetObstacleFilename(std::shared_ptr<CuboidObstacle> obstacle, PzG::GnuplotLink& link) {
    obstacle->AddFilename(link);
}