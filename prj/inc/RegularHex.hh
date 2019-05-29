#pragma once

#include "RightPrism.hh"

#define HEX_VERTEX_NUMB 12

/**
 * @brief Klasa modeluje pojecie graniastoslupa prawidlowwego
 *        szesciokatnego
 *
 */
class RegularHex : public RightPrism {
   private:
    double height;
    double edge_length;

   protected:
   public:
    RegularHex() : RightPrism() {}
    RegularHex(std::vector<Vector3D> vertex_vector) : RightPrism(vertex_vector) {}
    ~RegularHex() {}

    void Init(const Vector3D& middle_coords, double corpus_edge_length, double corpus_height,
              Vector3D orientation = Insert(0, 0, 0)) override;

    void Rotate(double Zrotation_angle, double Xrotation_angle = 0,
                double Yrotation_angle = 0) override;
};