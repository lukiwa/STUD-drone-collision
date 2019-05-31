#pragma once
#include <memory>
#include "CuboidObstacle.hh"
#include "SceneObject.hh"
#include "Vector3D.hh"

class ObstacleCreationInterface {
   public:
    ObstacleCreationInterface() = default;
    virtual ~ObstacleCreationInterface() = default;

    virtual std::shared_ptr<CuboidObstacle> CreateObstacle() = 0;
    virtual void SetObstacleParam(double height, double edge_length,
                                  const Vector3D& middle_coords) = 0;
    virtual void DeleteObstacle(std::shared_ptr<Drone> drone) = 0;
    virtual void SetObstacleFilename(std::shared_ptr<CuboidObstacle> obstacle,
                                     PzG::GnuplotLink& link) = 0;
};

struct ObstacleParameters : public ObstacleCreationInterface {
    Vector3D middle_coords;
    double edge_length;
    double height;
};
