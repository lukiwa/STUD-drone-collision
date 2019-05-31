#include "ObjectFactory.hh"

int ObjectFactory::created_drone_numb = 0;

void ObjectFactory::SetDroneParam(double height, double edge_length, double rotor_edge_length,
                                  double rotor_height, const Vector3D& corpus_middle_coords) {
    this->height = height;
    this->edge_length = edge_length;
    this->rotor_edge_length = rotor_edge_length;
    this->rotor_height = rotor_height;
    this->corpus_middle_coords = corpus_middle_coords;
}

std::shared_ptr<Drone> ObjectFactory::CreateDrone(PzG::GnuplotLink& link) {
    ++created_drone_numb;
    return std::make_shared<Drone>(this->height, this->edge_length, this->rotor_edge_length,
                                   this->rotor_height, this->corpus_middle_coords);
}

void ObjectFactory::DeleteDrone(std::shared_ptr<Drone> drone) {
    // TODO
}

void ObjectFactory::SetDroneFilename(std::shared_ptr<Drone> drone, PzG::GnuplotLink& link) {
    drone->AddMembersFilenames(link, created_drone_numb);
}