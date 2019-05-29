#pragma once

#include "RightPrism.hh"

/**
 * @brief Klasa modeluje pojecie prostopadloscianu
 *        Zawiera info o dlugosci bokow
 *
 */
class Cuboid : public RightPrism {
   private:
   protected:
   double edge_length;
   double height;
   public:
    Cuboid() : RightPrism() {}
    Cuboid(std::vector<Vector3D> vertex_vector) : RightPrism(vertex_vector) {}
    ~Cuboid() {}

    void Init(const Vector3D& middle_coords, double edge_length, double height,
              Vector3D orientation = Insert(0, 0, 0)) override;

    void Rotate(double Zrotation_angle, double Xrotation_angle = 0,
                double Yrotation_angle = 0) override;
};
