#pragma once
#include <fstream>
#include <iomanip>
#include <iostream>
#include "GeometricObject.hh"
#include "Matrix3x3.hh"

/**
 * @brief Klasa modeluje pojecie graniastoslupa
 *        prostego.Umozliwia rotacje takiego obiektu
 *
 */
class RightPrism : public GeometricObject<3> {
   private:
    void FillZAxisMatrix(double rotation_angle);
    void FillXAxisMatrix(double rotation_angle);
    void FillYAxisMatrix(double rotation_angle);

    Matrix3x3 rotation_matrix;

   protected:
    Vector3D orientation;  // trojka liczb okreslajaca orientacje graniastoslupa w przestrzeni
                           // kolejno x, y, z

    Vector3D build_point;  // punkt orientacyjny, ktory pozwala okreslic polozenie w ukladzie
                           // wspolrzednych
                           // NOTE najczesciej jest to punkt srodkowy danego graniastoslupai

    void RotateXAxis(double rotation_angle);
    void RotateYAxis(double rotation_angle);
    void RotateZAxis(double rotation_angle);

   public:
    RightPrism() { vertex_numb = 0; }
    RightPrism(std::vector<Vector3D> vertex_vector);
    ~RightPrism() {}

    void MoveByVector(const Vector3D &move_vector);

    /* ---------------------------- METODY WIRTUALNE ---------------------------- */
    virtual void Rotate(double Zrotation_angle, double Xrotation_angle = 0,
                        double Yrotation_angle = 0) = 0;
    virtual void Init(const Vector3D &build_point, double edge_length, double height,
                      Vector3D orientation = Insert(0, 0, 0)) = 0;

    std::ostream &WriteVertexAs4(std::ostream &stream) const;

    // TODO
    void Zero() {
        for (int i = 0; i < vertex_coords.size(); ++i) {
            for (int j = 0; j < 3; ++j) {
                vertex_coords[i][j] = 0;
            }
        }
    }
};
