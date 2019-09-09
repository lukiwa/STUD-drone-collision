#pragma once
#include "Cuboid.hh"
#include "CuboidObstacleContour.hh"
#include "Drone.hh"
#include "Obstacle.hh"

// NOTE unused
#define MAX_PROXIMITY 1  // maksymalna odleglosc na jaka moze zblizyc sie obiekt do

/**
 * @brief Definicuje pojecie przeszkody bedacej prostopadloscianem
 *
 */
class CuboidObstacle : public Obstacle, public Cuboid {
   private:
    mutable CuboidObstacleContour contour;  // kontur przeszkody(2 skrajne wektory)

   protected:
   public:
    // TODO usuniecie mozliwosci konstruowania poza singletonem
    CuboidObstacle() : Obstacle() {}
    CuboidObstacle(const Vector3D& middle_coords, double edge_length, double height,
                   PzG::GnuplotLink link, const Vector3D& orientation = Insert(0, 0, 0));
    ~CuboidObstacle() {}

    bool WriteWertexToFile() override;
    bool IsCollisionDetected(std::shared_ptr<Drone> drone) const override;
};
